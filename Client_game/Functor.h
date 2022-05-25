#pragma once
class Functor{
private:
	void* data_;
public:
	Functor(void* data);
	void* getData();
	virtual void call() {};
};

