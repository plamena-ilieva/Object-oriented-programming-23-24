#pragma once
class StringPool
{
	struct StringNode {
		char* str;
		unsigned refCount;

		void allocate(const char* data);

		StringNode(const StringNode& other) = delete;
		StringNode& operator=(const StringNode& other) = default;

		~StringNode() = default;
	};

	StringNode* data;
	unsigned size = 0;
	unsigned capacity;

	const char* addInternal(const char* str, int idx);
	void removeInternal(int idx);

	int lowerBound(const char* str, bool& isFound) const;

public:

	StringPool();
	StringPool(const StringPool&) = delete;
	StringPool operator=(const StringPool&) = delete;
	~StringPool();

	const char* add(const char* str);
	void remove(const char* str);
};

