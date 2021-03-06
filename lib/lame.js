/**
 * Opus encoding/decoding
 * @namespace opus
 */

const native = require('./native');

/**
 * @class lame.LameEncoder
 * @memberof opus
 * @classdesc An Opus Encoder and Decoder
 * @constructor
 * @param {Number} rate - The sample rate
 * @param {Number} channels - The number of channels
 */

/**
 * @memberof lame.LameEncoder
 * @method encode
 * @param {Buffer<PCM>} data - The input pcm data, may be null if piping from another NativeFunction
 * @returns {NativeFunction<Buffer<Opus>>} - A native function to be run with a {@link Chain}
 */

module.exports = {
  version: native.lameVersion,
  LameEncoder: native.LameEncoder,
};
