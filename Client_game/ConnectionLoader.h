#pragma once
#include "Loader.h"
#include "HttpRequester.h"
#include "RequestInformer.h"
#include <chrono>
#include <thread>

class ConnectionLoader : public Loader{
public:

	virtual void load(int* state);

	int getRegistered() const;

private:

	int registered_;

};

