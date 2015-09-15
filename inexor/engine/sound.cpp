// sound.cpp: basic positional sound using sdl_mixer

#include "inexor/engine/engine.h"
#include "inexor/shared/filesystem.h"

#include "SDL_mixer.h"
#define MAXVOL MIX_MAX_VOLUME

/// determins if sound is on or off (/soundvol 0?)
bool nosound = true;


/// structure to describe a sound sample
struct soundsample
{
    /// the name of the sound sample
    char *name;
    /// SDL documentation:
    /// The internal format for an audio chunk. This stores the sample data, the length in bytes of that data, and the volume to use when mixing the sample.
    /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_85.html
    Mix_Chunk *chunk;

    /// sound sample constructor
    soundsample() : name(NULL), chunk(NULL) {}
    /// sound sample destructor
    /// only deletes sound sample name (whose memory is being allocated dynamically)
    ~soundsample() { DELETEA(name); }

    /// cleans a chunk
    /// this function body has been reformatted!
    void cleanup() 
    {
        if(chunk)
        {
            /// SDL documentation:
            /// Free the memory used in chunk, and free chunk itself as well. 
            /// Do not use chunk after this without loading a new sample to it. 
            /// Note: It's a bad idea to free a chunk that is still being played... 
            /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_24.html#SEC24
            Mix_FreeChunk(chunk);
            chunk = NULL;
        }
    }

    /// ?
    bool load(bool msg = false);
};


/// A structure to describe a sound slot
struct soundslot
{
    /// A pointer to an instance of the sound sample structure
    soundsample *sample;
    /// the play volume of this slot
    int volume;
};

/// A structure to describe the configuration of the sound interface
struct soundconfig
{
    /// ?
    int slots;
    /// ?
    int numslots;
    /// number of ?
    int maxuses;

    /// ?
    /// @param p
    /// @param v
    bool hasslot(const soundslot *p, const vector<soundslot> &v) const
    {
        return p >= v.getbuf() + slots && p < v.getbuf() + slots+numslots && slots+numslots < v.length(); 
    }

    /// if there are many configs choose a random sound slot?
    int chooseslot() const
    {
        return numslots > 1 ? slots + rnd(numslots) : slots;
    }
};


/// A structure to describe a sound channel
struct soundchannel
{ 
    /// the unique identifier of this sound channel
    int id;
    /// describes if this sound channel is currently in use
    bool inuse;
    /// the 3D position of this sound channel
    vec loc;
    /// 
    soundslot *slot;
    /// the entity to which this sound channel is linked
    extentity *ent;

    /// these initialisations have been rewritten so every int is in an own line
    /// the radius of the sound channel
    int radius;
    /// the volume of the sound channel
    int volume;
    /// ?
    int pan;
    /// options seems to be stored in binary flags
    /// see binary operators &~
    int flags;
    /// ?
    bool dirty;

    /// constructor
    /// this function body has been reformatted
    /// initialise the sound channel's id via a constructor list
    /// TODO: why use a constructor list if id is not const?
    soundchannel(int id) : id(id)
    {
        /// reset the sound channel
        reset();
    }

    /// this function body has been reformatted
    /// TODO: ? check if this sound channel has a location?
    bool hasloc() const 
    {
        return loc.x >= -1e15f;
    }

    /// clear sound channel's location
    /// TODO: Why not use vec(0,0,0) ??
    void clearloc() 
    {
        loc = vec(-1e16f, -1e16f, -1e16f);
    }

    /// reset the sound channel
    void reset()
    {
        inuse = false;
        clearloc();
        slot = NULL;
        ent = NULL;
        radius = 0;
        /// TODO: why set volume to -1 instead of just 0?
        volume = -1;
        /// TODO: why set pan to -1 instead of just 0?
        pan = -1;
        flags = 0;
        /// TODO: why is it not "dirty" anymore??
        dirty = false;
    }
};

/// A (Sauerbraten) vector which contains the sound channels
vector<soundchannel> channels;

/// the maximum number of channels (that should be used?)
int maxchannels = 0;

/// create a new sound channel
/// @param n the ID of the sound channel
/// @param slot a pointer to the sound channel's sound slot
/// @param loc the location of the sound
/// @param ent a pointer to an entity which is linked to this sound (/newent sound)
/// @param flags additional binary flag options
/// @param radius the sound channel's radius
/// @return a reference to the sound channel that has been created
soundchannel &newchannel(int n, soundslot *slot, const vec *loc = NULL, extentity *ent = NULL, int flags = 0, int radius = 0)
{
    /// if this is a valid entity
    if(ent)
    {
        /// apply the entity's position as the sound channel's position
        loc = &ent->o;
        /// set the sound flag in this entity
        ent->flags |= EF_SOUND;
    }

    /// Add a sound channel at the end if it does not exist already
    while(!channels.inrange(n)) channels.add(channels.length());
    /// create a reference to the current sound channel
    soundchannel &chan = channels[n];

    /// save sound channel data and configuration
    chan.reset();
    chan.inuse = true;
    if(loc) chan.loc = *loc;
    chan.slot = slot;
    chan.ent = ent;
    chan.flags = 0;
    chan.radius = radius;
    return chan;
}


/// de-initialise and remove a channel by index
/// @param n the index of the sound channel
/// TODO: So it just de-initialises a sound channel but what happens to its data? will it be cleared? I dont see it.
void freechannel(int n)
{
    /// check if this channel is initialised
    if(!channels.inrange(n) || !channels[n].inuse) return;
    /// create a reference to the sound channel
    soundchannel &chan = channels[n];
    /// mark it as unused
    chan.inuse = false;
    /// if there is an entity associated with this sound channel
    /// remove the entity's sound flag
    if(chan.ent) chan.ent->flags &= ~EF_SOUND;
}

/// TODO: What does it mean when a channel is dirty?
/// does it mean that it is not synchronised with something??

/// TODO: synchronise a channel?
void syncchannel(soundchannel &chan)
{
    /// TODO: do not sync channels if they're not dirty?
    if(!chan.dirty) return;

    /// SDL documentation
    /// Tells you if which channel is fading in, out, or not.
    /// Does not tell you if the channel is playing anything, or paused, so you'd need to test that separately. 
    /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_40.html
    if(!Mix_FadingChannel(chan.id))
    {
        /// SDL documentation
        /// Set the volume for any allocated channel. If channel is -1 then all channels at are set at once.
        /// The volume is applied during the final mix, along with the sample volume.
        /// So setting this volume to 64 will halve the output of all samples played on the specifie
        /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_27.html
        Mix_Volume(chan.id, chan.volume);
    }

    /// TODO: what is panning?

    /// SDL documentation
    /// This effect will only work on stereo audio. Meaning you called Mix_OpenAudio with 2 channels (MIX_DEFAULT_CHANNELS). 
    /// The easiest way to do true panning is to call Mix_SetPanning(channel, left, 254 - left); 
    /// so that the total volume is correct, if you consider 
    /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_80.html
    Mix_SetPanning(chan.id, 255-chan.pan, chan.pan);

    /// TODO: not so dirty anymore?
    /// but how to determine if a sound channel is dirty?
    chan.dirty = false;
}

/// stop all channels from playing
void stopchannels()
{
    /// loop through the vector of channels
    loopv(channels)
    {
        /// create a reference to the current index channel
        soundchannel &chan = channels[i];
        /// skip this channel if it is not in use
        if(!chan.inuse) continue;

        /// SDL documentation
        /// Halt channel playback, or all channels if -1 is passed in.
        /// Any callback set by Mix_ChannelFinished will be called. 
        /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_34.html
        Mix_HaltChannel(i);

        /// TODO: Why does stopping all channels also free them?
        freechannel(i);
    }
}

/// TODO: so there can only be ONE background music track which is nice

/// the volume of sound effects and music
void setmusicvol(int musicvol);
VARFP(soundvol, 0, 255, 255, if(!soundvol) { stopchannels(); setmusicvol(0); });

/// the volume of background music
VARFP(musicvol, 0, 128, 255, setmusicvol(soundvol ? musicvol : 0));

/// the path/filenam of the current music track
char *musicfile = NULL;

/// The Sauerbraten CubeScript command which should be executed 
/// as soon as the music has stopped playing
char *musicdonecmd = NULL;

/// SDL documentation
/// This is an opaque data type used for Music data. 
/// This should always be used as a pointer. Who knows why it isn't a pointer in this typedef... 
/// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_86.html
Mix_Music *music = NULL;

/// SDL documentation
/// A structure that provides an abstract interface to stream I/O. 
/// Applications can generally ignore the specifics of this structure's internals and treat them as opaque pointers. 
/// The details are important to lower-level code that might need to implement one of these, however. 
/// https://wiki.libsdl.org/SDL_RWops
SDL_RWops *musicrw = NULL;

/// A Sauerbraten stream for music (Sauerbraten's toolset)
stream *musicstream = NULL;

/// set the volume of background music
/// @param musicvol the volume of the background music
void setmusicvol(int musicvol)
{
    /// if there is no sound enabled return
    if(nosound) return;
    if(music) 
    {
        /// SDL documentation
        /// Changes the volume of the currently playing music. 
        /// http://sdl.beuc.net/sdl.wiki/Mix_VolumeMusic
        Mix_VolumeMusic((musicvol*MAXVOL)/255);
    }
}

/// stop all music from playing
void stopmusic()
{
    if(nosound) return;
    /// delete music file pointer and 
    /// cubescript command pointer
    DELETEA(musicfile);
    DELETEA(musicdonecmd);
    if(music)
    {
        /// SDL documentation
        /// Halt playback of music. This interrupts music fader effects.
        /// Any callback set by Mix_HookMusicFinished will be called when the music stops.
        /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_67.html
        Mix_HaltMusic();

        /// SDL documentation
        /// Free the loaded music. If music is playing it will be halted.
        /// If music is fading out, then this function will wait (blocking) until the fade out is complete. 
        /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_56.html
        Mix_FreeMusic(music);
        music = NULL;
    }
    if(musicrw) 
    {
        /// SDL documentation
        /// Use this function to free an SDL_RWops structure allocated by SDL_AllocRW().
        /// https://wiki.libsdl.org/SDL_FreeRW
        SDL_FreeRW(musicrw); 
        musicrw = NULL;
    }
    /// delete musicstream
    DELETEP(musicstream);
}

/// TODO: how many sound channels can your processor calculate :) ?

/// the maximum amount of sound channels
VARF(soundchans, 1, 32, 128, initwarning("sound configuration", INIT_RESET, CHANGE_SOUND));

/// the sound's frequency
VARF(soundfreq, 0, 44100, 44100, initwarning("sound configuration", INIT_RESET, CHANGE_SOUND));

/// the sound buffer length
VARF(soundbufferlen, 128, 1024, 4096, initwarning("sound configuration", INIT_RESET, CHANGE_SOUND));


/// initialise sound
void initsound()
{
    /// SDL documentation
    /// Initialize the mixer API.
    /// This must be called before using other functions in this library.
    /// SDL must be initialized with SDL_INIT_AUDIO before this call. frequency would be 44100 for 44.1KHz, which is CD audio rate. 
    /// Most games use 22050, because 44100 requires too much CPU power on older computers. chunksize is the size of each mixed sample. 
    /// The smaller this is the more your hooks will be called. If make this too small on a slow system, sound may skip. If made to large, sound effects will lag behind the action more. 
    /// You want a happy medium for your target computer. You also may make this 4096, or larger, if you are just playing music.
    /// MIX_CHANNELS(8) mixing channels will be allocated by default. You may call this function multiple times, however you will have to call Mix_CloseAudio just as many times for the device to actually close. 
    /// The format will not changed on subsequent calls until fully closed. So you will have to close all the way before trying to open with different format parameters. 
    /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_11.html
    if(Mix_OpenAudio(soundfreq, MIX_DEFAULT_FORMAT, 2, soundbufferlen)<0)
    {
        /// now we have no sound :(
        nosound = true;
        /// SDL documentation
        /// Gets an SDL_Error. 
        /// http://sdl.beuc.net/sdl.wiki/Mix_GetError
        conoutf(CON_ERROR, "sound init failed (SDL_mixer): %s", Mix_GetError());
        return;
    }

    /// SDL documentation
    /// Set the number of channels being mixed. This can be called multiple times, even with sounds playing. 
    /// If numchans is less than the current number of channels, then the higher channels will be stopped, freed, and therefore not mixed any longer. 
    /// It's probably not a good idea to change the size 1000 times a second though.
    /// If any channels are deallocated, any callback set by Mix_ChannelFinished will be called when each channel is halted to be freed. 
    /// Note: passing in zero WILL free all mixing channels, however music will still play. 
    /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_26.html
	Mix_AllocateChannels(soundchans);
    	
    /// so maxsoundchannels is just linked to the Sauerbraten in-engine command var soundchans!
    maxchannels = soundchans;
    /// now we have sound!
    nosound = false;
}


/// This is a callback function!
/// As soon as music has stopped palying, call this function
void musicdone()
{
    if(music) 
    {
        /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_67.html
        Mix_HaltMusic(); 
        /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_56.html
        Mix_FreeMusic(music);
        music = NULL;
    }
    if(musicrw)
    {
        /// https://wiki.libsdl.org/SDL_FreeRW
        SDL_FreeRW(musicrw);
        musicrw = NULL;
    }
    DELETEP(musicstream);
    DELETEA(musicfile);
    if(!musicdonecmd) return;
    char *cmd = musicdonecmd;
    musicdonecmd = NULL;

    /// execute CubeScript "music has stopped playing" comamnd
    execute(cmd);
    delete[] cmd;
}


/// load a music file
/// @param name the name of the music file
Mix_Music *loadmusic(const char *name)
{
    if(!musicstream) musicstream = openzipfile(name, "rb");
    if(musicstream)
    {
        if(!musicrw) musicrw = musicstream->rwops();
        if(!musicrw) DELETEP(musicstream);
    }
    /// TODO: SDL mixer documentation?? what is that?
    if(musicrw) music = Mix_LoadMUSType_RW(musicrw, MUS_NONE, 0);
    /// SDL mixer documentation
    /// Load music file to use. This can load WAVE, MOD, MIDI, OGG, MP3, FLAC, and any file that you use a command to play with.
    /// If you are using an external command to play the music, you must call Mix_SetMusicCMD before this, otherwise the internal players will be used.
    /// Alternatively, if you have set an external command up and don't want to use it, you must call Mix_SetMusicCMD(NULL) to use the built-in players again. 
    /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_55.html
    else music = Mix_LoadMUS(findfile(name, "rb")); 
    if(!music)
    {
        if(musicrw) 
        {
            /// https://wiki.libsdl.org/SDL_FreeRW
            SDL_FreeRW(musicrw);
            musicrw = NULL;
        }
        DELETEP(musicstream);
    }
    return music;
}


/// start playing music
/// @param name the name of the music file
/// @param the 
void startmusic(char *name, char *cmd)
{
    if(nosound) return;
    stopmusic();
    if(soundvol && musicvol && *name)
    {
        string file;
        /// append Inexor media directory
        inexor::filesystem::appendmediadir(file, MAXSTRLEN, name, DIR_MUSIC);
        path(file);
        if(loadmusic(file))
        {
            DELETEA(musicfile);
            DELETEA(musicdonecmd);
            musicfile = newstring(file);
            if(cmd[0]) musicdonecmd = newstring(cmd);
            /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_57.html
            Mix_PlayMusic(music, cmd[0] ? 0 : -1);
            /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_61.html
            Mix_VolumeMusic((musicvol*MAXVOL)/255);
            intret(1);
        }
        else
        {
            /// failure: return 0 to CubeScript
            conoutf(CON_ERROR, "could not play music: %s", file);
            intret(0); 
        }
    }
}

/// Command to change background music
COMMANDN(music, startmusic, "ss");


/// Load a wave audio file
/// @param name the name of the WAVE file
static Mix_Chunk *loadwav(const char *name)
{
    Mix_Chunk *c = NULL;
    stream *z = openzipfile(name, "rb");
    if(z)
    {
        SDL_RWops *rw = z->rwops();
        if(rw)
        {
            /// SDL documentation
            /// Load src for use as a sample. This can load WAVE, AIFF, RIFF, OGG, and VOC formats. 
            /// Using SDL_RWops is not covered here, but they enable you to load from almost any source. 
            /// Note: You must call SDL_OpenAudio before this. It must know the output characteristics so it can convert the sample for playback, it does this conversion at load time. 
            /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_20.html
            c = Mix_LoadWAV_RW(rw, 0);
            /// https://wiki.libsdl.org/SDL_FreeRW
            SDL_FreeRW(rw);
        }
        delete z;
    }
    /// SDL documentation
    /// Load file for use as a sample. This is actually Mix_LoadWAV_RW(SDL_RWFromFile(file, "rb"), 1). 
    /// This can load WAVE, AIFF, RIFF, OGG, and VOC files.
    /// Note: You must call SDL_OpenAudio before this. 
    /// It must know the output characteristics so it can convert the sample for playback, it does this conversion at load time. 
    /// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_19.html
    if(!c) c = Mix_LoadWAV(findfile(name, "rb"));
    return c;
}


/// load a sound sample
bool soundsample::load(bool msg)
{
    if(chunk) return true;
    if(!name[0]) return false;

    /// the supported file extensions
    static const char * const exts[] = { "", ".ogg", ".flac", ".wav" };
    string filename;
    loopi(sizeof(exts)/sizeof(exts[0]))
    {
        /// append Inexor media directory
        inexor::filesystem::appendmediadir(filename, MAXSTRLEN, name, DIR_SOUND, exts[i]);
        /// render loading screen 
        if(msg && !i) renderprogress(0, filename);
        /// find and load wave
        path(filename);
        chunk = loadwav(filename);
        if(chunk) return true;
    }

    conoutf(CON_WARN, "failed to load sound: %s", filename);
    return false;
}

/// TODO: ?
static hashnameset<soundsample> samples;

/// TODO: clear all sound samples?
static void cleanupsamples()
{
    enumerate(samples, soundsample, s, s.cleanup());
}

static struct soundtype
{
    vector<soundslot> slots;
    vector<soundconfig> configs;

    int findsound(const char *name, int vol)
    {
        loopv(configs)
        {
            soundconfig &s = configs[i];
            loopj(s.numslots)
            {
                soundslot &c = slots[s.slots+j];
                if(!strcmp(c.sample->name, name) && (!vol || c.volume==vol)) return i;
            }
        }
        return -1;
    }

    int addslot(const char *name, int vol)
    {
        soundsample *s = samples.access(name);
        if(!s)
        {
            char *n = newstring(name);
            s = &samples[n];
            s->name = n;
            s->chunk = NULL;
        }
        soundslot *oldslots = slots.getbuf();
        int oldlen = slots.length();
        soundslot &slot = slots.add();
        // soundslots.add() may relocate slot pointers
        if(slots.getbuf() != oldslots) loopv(channels)
        {
            soundchannel &chan = channels[i];
            if(chan.inuse && chan.slot >= oldslots && chan.slot < &oldslots[oldlen])
                chan.slot = &slots[chan.slot - oldslots];
        }
        slot.sample = s;
        slot.volume = vol ? vol : 100;
        return oldlen;
    }

    int addsound(const char *name, int vol, int maxuses = 0)
    {
        soundconfig &s = configs.add();
        s.slots = addslot(name, vol);
        s.numslots = 1;
        s.maxuses = maxuses;
        return configs.length()-1;
    }

    void addalt(const char *name, int vol)
    {
        if(configs.empty()) return;
        addslot(name, vol);
        configs.last().numslots++;
    }

    void clear()
    {
        slots.setsize(0);
        configs.setsize(0);
    }

    void reset()
    {
        loopv(channels)
        {
            soundchannel &chan = channels[i];
            if(chan.inuse && slots.inbuf(chan.slot))
            {
                Mix_HaltChannel(i);
                freechannel(i);
            }
        }
        clear();
    }

    void preloadsound(int n)
    {
        if(nosound || !configs.inrange(n)) return;
        soundconfig &config = configs[n];
        loopk(config.numslots) slots[config.slots+k].sample->load(true);
    }

    bool playing(const soundchannel &chan, const soundconfig &config) const
    {
        return chan.inuse && config.hasslot(chan.slot, slots);
    }
} gamesounds, mapsounds;

void registersound(char *name, int *vol) { intret(gamesounds.addsound(name, *vol, 0)); }
COMMAND(registersound, "si");

void mapsound(char *name, int *vol, int *maxuses) { intret(mapsounds.addsound(name, *vol, *maxuses < 0 ? 0 : max(1, *maxuses))); }
COMMAND(mapsound, "sii");

void altsound(char *name, int *vol) { gamesounds.addalt(name, *vol); }
COMMAND(altsound, "si");

void altmapsound(char *name, int *vol) { mapsounds.addalt(name, *vol); }
COMMAND(altmapsound, "si");

void soundreset()
{
    gamesounds.reset();
}
COMMAND(soundreset, "");

void mapsoundreset()
{
    mapsounds.reset();
}
COMMAND(mapsoundreset, "");

void resetchannels()
{
    loopv(channels) if(channels[i].inuse) freechannel(i);
    channels.shrink(0);
}

void clear_sound()
{
    closemumble();
    if(nosound) return;
    stopmusic();

    cleanupsamples();
    gamesounds.clear();
    mapsounds.clear();
    samples.clear();
    Mix_CloseAudio();
    resetchannels();
}

void stopmapsounds()
{
    loopv(channels) if(channels[i].inuse && channels[i].ent)
    {
        Mix_HaltChannel(i);
        freechannel(i);
    }
}

void clearmapsounds()
{
    stopmapsounds();
    mapsounds.clear();
}

void stopmapsound(extentity *e)
{
    loopv(channels)
    {
        soundchannel &chan = channels[i];
        if(chan.inuse && chan.ent == e)
        {
            Mix_HaltChannel(i);
            freechannel(i);
        }
    }
}

void checkmapsounds()
{
    const vector<extentity *> &ents = entities::getents();
    loopv(ents)
    {
        extentity &e = *ents[i];
        if(e.type!=ET_SOUND) continue;
        if(camera1->o.dist(e.o) < e.attr2)
        {
            if(!(e.flags&EF_SOUND)) playsound(e.attr1, NULL, &e, SND_MAP, -1);
        }
        else if(e.flags&EF_SOUND) stopmapsound(&e);
    }
}

VAR(stereo, 0, 1, 1);

VARP(maxsoundradius, 0, 340, 10000);

bool updatechannel(soundchannel &chan)
{
    if(!chan.slot) return false;
    int vol = soundvol, pan = 255/2;
    if(chan.hasloc())
    {
        vec v;
        float dist = chan.loc.dist(camera1->o, v);
        int rad = maxsoundradius;
        if(chan.ent)
        {
            rad = chan.ent->attr2;
            if(chan.ent->attr3)
            {
                rad -= chan.ent->attr3;
                dist -= chan.ent->attr3;
            }
        }
        else if(chan.radius > 0) rad = maxsoundradius ? min(maxsoundradius, chan.radius) : chan.radius;
        if(rad > 0) vol -= int(clamp(dist/rad, 0.0f, 1.0f)*soundvol); // simple mono distance attenuation
        if(stereo && (v.x != 0 || v.y != 0) && dist>0)
        {
            v.rotate_around_z(-camera1->yaw*RAD);
            pan = int(255.9f*(0.5f - 0.5f*v.x/v.magnitude2())); // range is from 0 (left) to 255 (right)
        }
    }
    vol = (vol*MAXVOL*chan.slot->volume)/255/255;
    vol = min(vol, MAXVOL);
    if(vol == chan.volume && pan == chan.pan) return false;
    chan.volume = vol;
    chan.pan = pan;
    chan.dirty = true;
    return true;
}  

void reclaimchannels()
{
    loopv(channels)
    {
        soundchannel &chan = channels[i];
        if(chan.inuse && !Mix_Playing(i)) freechannel(i);
    }
}

void syncchannels()
{
        loopv(channels) 
        {
            soundchannel &chan = channels[i];
        if(chan.inuse && chan.hasloc() && updatechannel(chan)) syncchannel(chan);
        }
}

void updatesounds()
{
    updatemumble();
    if(nosound) return;
    if(minimized) stopsounds();
    else
    {
        reclaimchannels();
        if(mainmenu) stopmapsounds();
        else checkmapsounds();
        syncchannels();
    }
    if(music)
    {
        if(!Mix_PlayingMusic()) musicdone();
        else if(Mix_PausedMusic()) Mix_ResumeMusic();
    }
}

VARP(maxsoundsatonce, 0, 7, 100);

VAR(dbgsound, 0, 0, 1);

void preloadsound(int n)
{
    gamesounds.preloadsound(n);
}

void preloadmapsound(int n)
{
    mapsounds.preloadsound(n);
}

void preloadmapsounds()
{
    const vector<extentity *> &ents = entities::getents();
    loopv(ents)
    {
        extentity &e = *ents[i];
        if(e.type==ET_SOUND) mapsounds.preloadsound(e.attr1);
    }
}
 
int playsound(int n, const vec *loc, extentity *ent, int flags, int loops, int fade, int chanid, int radius, int expire)
{
    if(nosound || !soundvol || minimized) return -1;

    soundtype &sounds = ent || flags&SND_MAP ? mapsounds : gamesounds;
    if(!sounds.configs.inrange(n)) { conoutf(CON_WARN, "unregistered sound: %d", n); return -1; }
    soundconfig &config = sounds.configs[n];

    if(loc && (maxsoundradius || radius > 0))
    {
        // cull sounds that are unlikely to be heard
        int rad = radius > 0 ? (maxsoundradius ? min(maxsoundradius, radius) : radius) : maxsoundradius;
        if(camera1->o.dist(*loc) > 1.5f*rad)
        {
            if(channels.inrange(chanid) && sounds.playing(channels[chanid], config))
            {
                Mix_HaltChannel(chanid);
                freechannel(chanid);
            }
            return -1;    
        }
    }

    if(chanid < 0)
    {
        if(config.maxuses)
        {
            int uses = 0;
            loopv(channels) if(sounds.playing(channels[i], config) && ++uses >= config.maxuses) return -1;
        }

        // avoid bursts of sounds with heavy packetloss and in sp
        static int soundsatonce = 0, lastsoundmillis = 0;
        if(totalmillis == lastsoundmillis) soundsatonce++; else soundsatonce = 1;
        lastsoundmillis = totalmillis;
        if(maxsoundsatonce && soundsatonce > maxsoundsatonce) return -1;
    }

    if(channels.inrange(chanid))
    {
        soundchannel &chan = channels[chanid];
        if(sounds.playing(chan, config))
        {
            if(loc) chan.loc = *loc;
            else if(chan.hasloc()) chan.clearloc();
            return chanid;
        }
    }
    if(fade < 0) return -1;

    soundslot &slot = sounds.slots[config.chooseslot()];
    if(!slot.sample->chunk && !slot.sample->load()) return -1;

    if(dbgsound) conoutf("sound: %s", slot.sample->name);
 
    chanid = -1;
    loopv(channels) if(!channels[i].inuse) { chanid = i; break; }
    if(chanid < 0 && channels.length() < maxchannels) chanid = channels.length();
    if(chanid < 0) loopv(channels) if(!channels[i].volume) { Mix_HaltChannel(i); freechannel(i); chanid = i; break; }
    if(chanid < 0) return -1;

    soundchannel &chan = newchannel(chanid, &slot, loc, ent, flags, radius);
    updatechannel(chan);
    int playing = -1;
    if(fade) 
    {
        Mix_Volume(chanid, chan.volume);
        playing = expire >= 0 ? Mix_FadeInChannelTimed(chanid, slot.sample->chunk, loops, fade, expire) : Mix_FadeInChannel(chanid, slot.sample->chunk, loops, fade);
    }
    else playing = expire >= 0 ? Mix_PlayChannelTimed(chanid, slot.sample->chunk, loops, expire) : Mix_PlayChannel(chanid, slot.sample->chunk, loops);
    if(playing >= 0) syncchannel(chan); 
    else freechannel(chanid);
    return playing;
}

void stopsounds()
{
    loopv(channels) if(channels[i].inuse)
    {
        Mix_HaltChannel(i);
        freechannel(i);
    }
}

bool stopsound(int n, int chanid, int fade)
{
    if(!gamesounds.configs.inrange(n) || !channels.inrange(chanid) || !channels[chanid].inuse || !gamesounds.playing(channels[chanid], gamesounds.configs[n])) return false;
    if(dbgsound) conoutf("stopsound: %s", channels[chanid].slot->sample->name);
    if(!fade || !Mix_FadeOutChannel(chanid, fade))
    {
        Mix_HaltChannel(chanid);
        freechannel(chanid);
    }
    return true;
}

int playsoundname(const char *s, const vec *loc, int vol, int flags, int loops, int fade, int chanid, int radius, int expire) 
{ 
    if(!vol) vol = 100;
    int id = gamesounds.findsound(s, vol);
    if(id < 0) id = gamesounds.addsound(s, vol);
    return playsound(id, loc, NULL, flags, loops, fade, chanid, radius, expire);
}

void sound(int *n) { playsound(*n); }
COMMAND(sound, "i");

void resetsound()
{
    clearchanges(CHANGE_SOUND);
    if(!nosound) 
    {
        cleanupsamples();
        if(music)
        {
            Mix_HaltMusic();
            Mix_FreeMusic(music);
        }
        if(musicstream) musicstream->seek(0, SEEK_SET);
        Mix_CloseAudio();
    }
    initsound();
    resetchannels();
    if(nosound)
    {
        DELETEA(musicfile);
        DELETEA(musicdonecmd);
        music = NULL;
        cleanupsamples();
        return;
    }
    if(music && loadmusic(musicfile))
    {
        Mix_PlayMusic(music, musicdonecmd ? 0 : -1);
        Mix_VolumeMusic((musicvol*MAXVOL)/255);
    }
    else
    {
        DELETEA(musicfile);
        DELETEA(musicdonecmd);
    }
}

COMMAND(resetsound, "");



/// In this section Mumble Positional Audio is handled.
/// TODO: Mumble Positional Audio seems to be broken??

#ifdef WIN32

#include <wchar.h>

#else

#include <unistd.h>

#ifdef _POSIX_SHARED_MEMORY_OBJECTS
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <wchar.h>
#endif

#endif

#if defined(WIN32) || defined(_POSIX_SHARED_MEMORY_OBJECTS)
struct MumbleInfo
{
    int version, timestamp;
    vec pos, front, top;
    wchar_t name[256];
};
#endif

#ifdef WIN32
static HANDLE mumblelink = NULL;
static MumbleInfo *mumbleinfo = NULL;
#define VALID_MUMBLELINK (mumblelink && mumbleinfo)
#elif defined(_POSIX_SHARED_MEMORY_OBJECTS)
static int mumblelink = -1;
static MumbleInfo *mumbleinfo = (MumbleInfo *)-1; 
#define VALID_MUMBLELINK (mumblelink >= 0 && mumbleinfo != (MumbleInfo *)-1)
#endif

#ifdef VALID_MUMBLELINK
VARFP(mumble, 0, 1, 1, { if(mumble) initmumble(); else closemumble(); });
#else
VARFP(mumble, 0, 0, 1, { if(mumble) initmumble(); else closemumble(); });
#endif

void initmumble()
{
    if(!mumble) return;
#ifdef VALID_MUMBLELINK
    if(VALID_MUMBLELINK) return;

    #ifdef WIN32
        mumblelink = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "MumbleLink");
        if(mumblelink)
        {
            mumbleinfo = (MumbleInfo *)MapViewOfFile(mumblelink, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MumbleInfo));
            if(mumbleinfo) wcsncpy(mumbleinfo->name, L"Inexor", 256);
        }
    #elif defined(_POSIX_SHARED_MEMORY_OBJECTS)
        defformatstring(shmname, "/MumbleLink.%d", getuid());
        mumblelink = shm_open(shmname, O_RDWR, 0);
        if(mumblelink >= 0)
        {
            mumbleinfo = (MumbleInfo *)mmap(NULL, sizeof(MumbleInfo), PROT_READ|PROT_WRITE, MAP_SHARED, mumblelink, 0);
            if(mumbleinfo != (MumbleInfo *)-1) wcsncpy(mumbleinfo->name, L"Inexor", 256);
        }
    #endif
    if(!VALID_MUMBLELINK) closemumble();
#else
    conoutf(CON_ERROR, "Mumble positional audio is not available on this platform.");
#endif
}

void closemumble()
{
#ifdef WIN32
    if(mumbleinfo) { UnmapViewOfFile(mumbleinfo); mumbleinfo = NULL; }
    if(mumblelink) { CloseHandle(mumblelink); mumblelink = NULL; }
#elif defined(_POSIX_SHARED_MEMORY_OBJECTS)
    if(mumbleinfo != (MumbleInfo *)-1) { munmap(mumbleinfo, sizeof(MumbleInfo)); mumbleinfo = (MumbleInfo *)-1; } 
    if(mumblelink >= 0) { close(mumblelink); mumblelink = -1; }
#endif
}

static inline vec mumblevec(const vec &v, bool pos = false)
{
    // change from X left, Z up, Y forward to X right, Y up, Z forward
    // 8 cube units = 1 meter
    vec m(-v.x, v.z, v.y);
    if(pos) m.div(8);
    return m;
}

void updatemumble()
{
#ifdef VALID_MUMBLELINK
    if(!VALID_MUMBLELINK) return;

    static int timestamp = 0;

    mumbleinfo->version = 1;
    mumbleinfo->timestamp = ++timestamp;

    mumbleinfo->pos = mumblevec(player->o, true);
    mumbleinfo->front = mumblevec(vec(RAD*player->yaw, RAD*player->pitch));
    mumbleinfo->top = mumblevec(vec(RAD*player->yaw, RAD*(player->pitch+90)));
#endif
}

