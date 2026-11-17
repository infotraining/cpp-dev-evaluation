#include "task_10_solution.hpp"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace Solution
{
namespace
{
class MapStorage : public Storage
{
public:
    explicit MapStorage(bool uppercase) : uppercase_(uppercase)
    {
    }

    void put(std::string key, std::string value) override
    {
        storage_[normalize(std::move(key))] = std::move(value);
    }

    std::optional<std::string> get(const std::string& key) const override
    {
        const auto iterator = storage_.find(normalize(key));
        if (iterator == storage_.end())
        {
            return std::nullopt;
        }
        return iterator->second;
    }

private:
    std::string normalize(std::string key) const
    {
        if (uppercase_)
        {
            std::ranges::transform(key, key.begin(), [](unsigned char ch) {
                return static_cast<char>(std::toupper(ch));
            });
        }
        return key;
    }

    bool uppercase_;
    std::unordered_map<std::string, std::string> storage_;
};
}

std::unique_ptr<Storage> MemoryStorageFactory::create() const
{
    return std::make_unique<MapStorage>(false);
}

std::unique_ptr<Storage> UppercaseStorageFactory::create() const
{
    return std::make_unique<MapStorage>(true);
}

StorageProxy::StorageProxy(std::unique_ptr<StorageFactory> factory) : factory_(std::move(factory))
{
    if (!factory_)
    {
        throw std::invalid_argument("storage proxy requires a factory");
    }
}

void StorageProxy::ensure_initialized() const
{
    if (!storage_)
    {
        storage_ = factory_->create();
        if (!storage_)
        {
            throw std::runtime_error("storage factory returned null");
        }
    }
}

void StorageProxy::put(std::string key, std::string value)
{
    ensure_initialized();
    storage_->put(std::move(key), std::move(value));
}

std::optional<std::string> StorageProxy::get(const std::string& key) const
{
    ensure_initialized();
    return storage_->get(key);
}

bool StorageProxy::initialized() const
{
    return storage_ != nullptr;
}
}
