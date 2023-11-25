#include <mutex>

class DatabaseAccess {
public:
	void create_table()
	{
		std::lock_guard<std::mutex> lg{ db_mutex };
		//...
	}

	void insert_data()
	{
		std::lock_guard<std::mutex> lg{ db_mutex };
		//..
	}

	void create_table_and_insert_data()
	{
		std::lock_guard<std::mutex> lg{ db_mutex };
		create_table();
		//...
	}
private:
	std::mutex db_mutex;
	//...
};

int main()
{
	DatabaseAccess dx;

	dx.create_table_and_insert_data(); //deadlock
}
