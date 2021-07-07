#include <iostream>
#include <thread>
#include <future>
using namespace std;


struct ARGS {
	string name;
	int num;
};

void worker1(string name, int num)
{
	for (int i = 0; i < num; ++i) {
		this_thread::sleep_for(chrono::milliseconds(100));
		cout << name << " count: " << i << endl;
	}
}

int worker2(void* pArgs)
{
	if (pArgs == nullptr) {
		throw std::runtime_error{ "Error: pArgs == null!" };
	}

	ARGS *args = (ARGS*) pArgs;

	int cnt;
	for (cnt = 0; cnt < args->num; ++cnt) {
		this_thread::sleep_for(chrono::milliseconds(500));
		cout /* << this_thread::get_id() << " "*/ << args->name << " count: " << cnt << endl;
	}
	return cnt;
}


int main()
{
	cout << "Running ..." << endl;

	ARGS args {"worker1", 10};

	try {

		auto fut1 = std::async(worker2, &args);
		cout << fut1.get() << endl;

	}
	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
}
