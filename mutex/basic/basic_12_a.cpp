class A {
	//...
};

A* gpa{ nullptr };

void foo()
{
	if (!gpa) {		   //not thread-safe
		gpa = new A;
	}
}
