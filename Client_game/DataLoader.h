#pragma once
#include "Loader.h"
#include "nlohmann/json.hpp"
#include "HttpRequester.h"
#include "RequestInformer.h"
#include <fstream>
class DataLoader :  public Loader{
public:
	DataLoader();
	virtual void load(int* state);
	int getLoaded() const;

private:

	int loaded_;

};

