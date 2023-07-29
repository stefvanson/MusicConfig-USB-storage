#include "music_config.h"

#include "hal.h"

void MusicConfig::dump() {
  log_print("Dumping MusicConfig:\n");
  log_print("  synth_notes:   {%i, %i, %i, %i, %i, %i, %i, %i}\n",
            synth_notes[0], synth_notes[1], synth_notes[2], synth_notes[3],
            synth_notes[4], synth_notes[5], synth_notes[6], synth_notes[7]);
  log_print("  bass_notes:    {%i, %i, %i, %i, %i, %i, %i, %i}\n",
            bass_notes[0], bass_notes[1], bass_notes[2], bass_notes[3],
            bass_notes[4], bass_notes[5], bass_notes[6], bass_notes[7]);
  log_print("  drum_notes[0]: {%i, %i, %i, %i, %i, %i, %i, %i}\n",
            drum_notes[0][0], drum_notes[0][1], drum_notes[0][2], drum_notes[0][3],
            drum_notes[0][4], drum_notes[0][5], drum_notes[0][6], drum_notes[0][7]);
  log_print("  drum_notes[1]: {%i, %i, %i, %i, %i, %i, %i, %i}\n",
            drum_notes[1][0], drum_notes[1][1], drum_notes[1][2], drum_notes[1][3],
            drum_notes[1][4], drum_notes[1][5], drum_notes[1][6], drum_notes[1][7]);
  log_print("  drum_notes[2]: {%i, %i, %i, %i, %i, %i, %i, %i}\n",
            drum_notes[2][0], drum_notes[2][1], drum_notes[2][2], drum_notes[2][3],
            drum_notes[2][4], drum_notes[2][5], drum_notes[2][6], drum_notes[2][7]);
}
