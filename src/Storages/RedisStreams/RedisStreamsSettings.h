#pragma once

#include <Core/BaseSettings.h>
#include <Core/Settings.h>


namespace DB
{
class ASTStorage;


#define REDIS_STREAMS_RELATED_SETTINGS(M) \
    M(String, redis_broker, "", "Redis broker for Redis Streams engine.", 0) \
    M(String, redis_stream_list, "", "A list of Redis Streams streams.", 0) \
    M(String, redis_group_name, "", "Client group id string.", 0) \
    M(String, redis_common_consumer_id, "", "Common identifier for consumers. Must be unique within group", 0) \
    M(UInt64, redis_num_consumers, 1, "The number of consumers per table for Redis engine.", 0) \
    M(Bool, redis_manage_consumer_groups, false, "Create consumer groups on engine startup and delete them at the end.", 0) \
    M(String, redis_consumer_groups_start_id, "$", "The message id from which the consumer groups will start to read.", 0) \
    M(Bool, redis_ack_every_batch, false, "Ack every consumed and handled batch instead of a single commit after writing a whole block/", 0) \
    M(Bool, redis_ack_on_select, true, "Ack messages after select query.", 0) \
    M(Milliseconds, redis_poll_timeout_ms, 0, "Timeout for single poll from Redis.", 0) \
    M(UInt64, redis_poll_max_batch_size, 0, "Maximum amount of messages to be read in a single Redis poll.", 0) \
    M(UInt64, redis_claim_max_batch_size, 0, "Maximum amount of messages to be claimed in a single Redis poll.", 0) \
    M(Milliseconds, redis_min_time_for_claim, 10000, "Minimum time in milliseconds after which consumers will start to claim messages.", 0) \
    M(UInt64, redis_max_block_size, 0, "Number of row collected by poll(s) for flushing data from Redis.", 0) \
    M(Milliseconds, redis_flush_interval_ms, 0, "Timeout for flushing data from Redis.", 0) \
    M(Bool, redis_thread_per_consumer, false, "Provide independent thread for each consumer.", 0) \
    M(String, redis_password, "", "Redis password.", 0)

#define LIST_OF_REDIS_STREAMS_SETTINGS(M) \
    REDIS_STREAMS_RELATED_SETTINGS(M) \
    FORMAT_FACTORY_SETTINGS(M)

DECLARE_SETTINGS_TRAITS(RedisStreamsSettingsTraits, LIST_OF_REDIS_STREAMS_SETTINGS)


/** Settings for the Redis engine.
  * Could be loaded from a CREATE TABLE query (SETTINGS clause).
  */
struct RedisStreamsSettings : public BaseSettings<RedisStreamsSettingsTraits>
{
    void loadFromQuery(ASTStorage & storage_def);
};

}
