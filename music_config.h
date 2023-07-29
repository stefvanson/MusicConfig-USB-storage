#ifndef MUSIC_CONFIG_H_
#define MUSIC_CONFIG_H_

constexpr int NUM_STEPS = 8;
constexpr int NUM_DRUM_TRACKS = 3;

class MusicConfig {
 public:
  int synth_notes[NUM_STEPS] = {0};
  int bass_notes[NUM_STEPS] = {0};
  int drum_notes[NUM_DRUM_TRACKS][NUM_STEPS] = {{0}};
  void dump();
};

#endif // MUSIC_CONFIG_H_
