#include <mutex>

class DatabaseAccess {
public:
	void createTable()
	{
		std::lock_guard<std::mutex> lg{ db_mutex };
		//...
	}

	void insertData()
	{
		std::lock_guard<std::mutex> lg{ db_mutex };
		//..
	}

	void createTableAndInsertData()
	{
		std::lock_guard<std::mutex> lg{ db_mutex };
		createTable();
		//...
	}
private:
	std::mutex db_mutex;
	//...
};
