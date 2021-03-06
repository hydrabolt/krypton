#include "main.h"
#include "PCM.h"
#include "Opus.h"

#include <cmath>
#include <cstdint>
#include <cstdlib>

namespace PCM {

Pipe *Volume16(void *req) {
  Args *args = static_cast<Args *>(req);
  Volume16Args *volumeArgs = static_cast<Volume16Args *>(args->args);
  Pipe *ret = new Pipe;

  int length = volumeArgs->length / 2;
  int16_t *data = volumeArgs->data;
  if (args->from == "Pipe") {
    Pipe *pipe = static_cast<Pipe *>(args->pipe);

    length = pipe->length / 2;
    data = reinterpret_cast<int16_t *>(pipe->data);
  }

  ret->length = length * 2;

  if (volumeArgs->volume == 1) {
    ret->data = reinterpret_cast<char *>(data);
  } else {
    int bytes = 2;
    int max = static_cast<int>(pow(2, 16 - 1)) - 1;
    int complete = static_cast<int>(floor(length / bytes)) * bytes;
    int16_t *sdata = static_cast<int16_t *>(malloc(length * sizeof(int16_t)));

    for (int i = 0; i < complete; i++) {
      sdata[i] = static_cast<int16_t>(fmin(max, fmax(-max, floor(volumeArgs->volume * data[i]))));
    }

    ret->data = reinterpret_cast<char *>(sdata);

    free(data);
  }

  if (args->from == "Pipe") {
    Pipe *pipe = static_cast<Pipe *>(args->pipe);

    if (volumeArgs->volume != 1) {
      free(pipe->data);
    }

    delete pipe;
  }

  delete args;
  delete volumeArgs;

  return ret;
}

}  // namespace PCM
