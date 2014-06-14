/**
 * Created by airead on 14-6-13.
 */
(function () {
    var bunyan, logger, streams;

    bunyan = require("bunyan");

    streams = [];

    streams.push({
        stream: process.stderr,
        level: 'trace'
    });

    logger = bunyan.createLogger({
        name: 'proC',
        streams: streams
    });

    logger.on('error', function (err, stream) {
        logger.fatal({
            err: err,
            stream: stream
        }, 'logger.on error');
    });

    logger.muteAll = function () {
        return logger.streams = [];
    };

    module.exports = logger;

}).call(this);

//# sourceMappingURL=index.map
