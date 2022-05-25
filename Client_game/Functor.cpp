#include "Functor.h"

Functor::Functor(void* data){

	data_ = data;

}

void* Functor::getData(){

	return data_;

}
