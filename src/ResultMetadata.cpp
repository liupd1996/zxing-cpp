/*
* Copyright 2016 ZXing authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "ResultMetadata.h"

#include "ZXString.h"
#include "ByteArray.h"

namespace ZXing {

struct ResultMetadata::Value
{
	virtual ~Value() {}
	virtual int toInteger(int fallback) const {
		return fallback;
	}
	virtual String toString() const {
		return String();
	}
	virtual std::list<ByteArray> toByteArrayList() const {
		return std::list<ByteArray>();
	}
	virtual std::shared_ptr<CustomData> toCustomData() const {
		return nullptr;
	}
};

struct ResultMetadata::IntegerValue : public Value
{
	int value;
	IntegerValue(int v) : value(v) {}
	virtual int toInteger(int fallback) const override {
		return value;
	}
};

struct ResultMetadata::StringValue : public Value
{
	String value;
	StringValue(const String& v) : value(v) {}
	virtual String toString() const override {
		return value;
	}
};

struct ResultMetadata::ByteArrayListValue : public Value
{
	std::list<ByteArray> value;
	ByteArrayListValue(const std::list<ByteArray>& v) : value(v) {}
	virtual std::list<ByteArray> toByteArrayList() const override {
		return value;
	}
};

struct ResultMetadata::CustomDataValue : public Value
{
	std::shared_ptr<CustomData> value;
	CustomDataValue(const std::shared_ptr<CustomData>& v) : value(v) {}
	virtual std::shared_ptr<CustomData> toCustomData() const override {
		return value;
	}
};

int
ResultMetadata::getInt(Key key, int fallback) const
{
	auto it = _contents.find(key);
	return it != _contents.end() ? it->second->toInteger(fallback) : fallback;
}

String
ResultMetadata::getString(Key key) const
{
	auto it = _contents.find(key);
	return it != _contents.end() ? it->second->toString() : String();
}

std::list<ByteArray>
ResultMetadata::getByteArrayList(Key key) const
{
	auto it = _contents.find(key);
	return it != _contents.end() ? it->second->toByteArrayList() : std::list<ByteArray>();
}

std::shared_ptr<CustomData>
ResultMetadata::getCustomData(Key key) const
{
	auto it = _contents.find(key);
	return it != _contents.end() ? it->second->toCustomData() : nullptr;
}

void
ResultMetadata::put(Key key, int value)
{
	_contents[key] = std::make_shared<IntegerValue>(value);
}

void
ResultMetadata::put(Key key, const String& value)
{
	_contents[key] = std::make_shared<StringValue>(value);
}

void
ResultMetadata::put(Key key, const std::list<ByteArray>& value)
{
	_contents[key] = std::make_shared<ByteArrayListValue>(value);
}

void
ResultMetadata::put(Key key, const std::shared_ptr<CustomData>& value)
{
	_contents[key] = std::make_shared<CustomDataValue>(value);
}

void
ResultMetadata::putAll(const ResultMetadata& other)
{
	_contents.insert(other._contents.begin(), other._contents.end());
}

} // ZXing
