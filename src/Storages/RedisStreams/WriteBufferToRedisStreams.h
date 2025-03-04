#pragma once

#include <Columns/IColumn.h>
#include <IO/WriteBuffer.h>
#include <boost/algorithm/string.hpp>
#include <redis++/redis++.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

#include <list>

namespace DB
{
class Block;
using RedisPtr = std::shared_ptr<sw::redis::Redis>;

class WriteBufferToRedisStreams : public WriteBuffer
{
public:
    WriteBufferToRedisStreams(
        RedisPtr redis_,
        const std::string & stream_,
        std::optional<char> delimiter,
        size_t rows_per_message,
        size_t chunk_size_);
    ~WriteBufferToRedisStreams() override;

    void countRow();

private:
    void nextImpl() override;
    void addChunk();
    void reinitializeChunks();
    static std::vector<std::pair<std::string, std::string>> convertRawPayloadToItems(const std::string & payload);

    RedisPtr redis;
    const std::string stream;
    const std::optional<char> delim;
    const size_t max_rows;
    const size_t chunk_size;

    size_t rows = 0;
    std::list<std::string> chunks;
    std::optional<size_t> timestamp_column_index;
};

}
