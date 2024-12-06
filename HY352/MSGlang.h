#include <iostream>
#include <string>
#include <cstdarg>
#include <list>
#include <algorithm>
#include <map>
#include <functional>
#include <sstream>

using namespace std;

#define let Object
#define none NULL
#define values valsobj,
#define lambda []
#define ref refa
#define func(name) key(name) = []
#define nl "\n"
#define args_list argumentList()

class val;
class vals;
class key;
class Object;

typedef std::map<string, val> Map;

val self(val i);
val arg(val i);
void eval(string id);
void change(val* MapValBuffer);

val* MapValBuffer;
Map keyfuncBufferMap;
string keyidbuffer;

class val {
private:
public:
	int intValue = none;
	double doubleValue = none;
	const char* stringValue = "";
	Map objectMap;
	function<val()> funcVal;
	bool boolValue = none, isInt = false, isDouble = false, isString = false, isBool = false, isObject = false, isFunc = false;

	val() {};
	val(int intValue) {
		this->intValue = intValue;
		isInt = true;
	};
	val(double doubleValue) {
		this->doubleValue = doubleValue;
		isDouble = true;
	};
	val(const char* stringValue) {
		this->stringValue = stringValue;
		isString = true;
	};
	val(bool boolValue) {
		this->boolValue = boolValue;
		isBool = true;
	};
	val(Map objectMap) {
		this->objectMap = objectMap;
		isObject = true;
	}
	val(function<val()> funcVal) {
		this->funcVal = funcVal;
		isFunc = true;
	};
	void operator= (int Value) {
		change(MapValBuffer);
		MapValBuffer->intValue = Value;
		MapValBuffer->isInt = true;
	};
	void operator= (double Value) {
		change(MapValBuffer);
		MapValBuffer->doubleValue = Value;
		MapValBuffer->isDouble = true;
	};
	void operator= (const char* Value) {
		change(MapValBuffer);
		MapValBuffer->stringValue = Value;
		MapValBuffer->isString = true;
	};
	void operator= (bool Value) {
		change(MapValBuffer);
		MapValBuffer->boolValue = Value;
		MapValBuffer->isBool = true;
	};
	void operator= (Map Value) {
		change(MapValBuffer);
		MapValBuffer->objectMap = Value;
		MapValBuffer->isObject = true;
	}
	void operator= (function <val()> funcVal) {
		change(MapValBuffer);
		MapValBuffer->funcVal = funcVal;
		MapValBuffer->isFunc = true;
	};
	void operator= (val Value) {
		if (Value.isInt == true) Value = Value.intValue;
		else if (Value.isDouble == true) Value = Value.doubleValue;
		else if (Value.isBool == true) Value = Value.boolValue;
		else if (Value.isString == true) Value = Value.stringValue;
	};
	void operator=(Object object);
	friend ostream& operator<< (ostream& os, val myValue);
	friend val operator+ (val x, val y);
	friend val operator- (val x, val y);
	friend val operator/ (val x, val y);
	friend val operator* (val x, val y);
	friend val operator% (val x, val y);
	friend bool operator== (val x, val y);
	friend bool operator!= (val x, val y);
	friend bool operator<= (val x, val y);
	friend bool operator>= (val x, val y);
	friend bool operator< (val x, val y);
	friend bool operator> (val x, val y);
};

val operator+ (val x, val y) {
	if (x.isInt == true && y.isInt == true) return x.intValue + y.intValue;
	else if (x.isInt == true && y.isDouble == true) return x.intValue + y.doubleValue;
	else if (x.isInt == true && y.isBool == true) return x.intValue + y.boolValue;
	else if (x.isInt == true && y.isString == true) return x.intValue + y.stringValue;
	else if (x.isDouble == true && y.isInt == true) return x.doubleValue + y.intValue;
	else if (x.isDouble == true && y.isDouble == true) return x.doubleValue + y.doubleValue;
	else if (x.isDouble == true && y.isBool == true) return x.doubleValue + y.boolValue;
	else if (x.isBool == true && y.isInt == true) return x.boolValue + y.intValue;
	else if (x.isBool == true && y.isDouble == true) return x.boolValue + y.doubleValue;
	else if (x.isBool == true && y.isBool == true) return x.boolValue + y.boolValue;
	else if (x.isBool == true && y.isString == true) return x.boolValue + y.stringValue;
	else if (x.isString == true && y.isInt == true) return x.stringValue + y.intValue;
	else if (x.isString == true && y.isBool == true) return x.stringValue + y.boolValue;
	return none;
};
val operator- (val x, val y) {
	if (x.isInt == true && y.isInt == true) return x.intValue - y.intValue;
	else if (x.isInt == true && y.isDouble == true) return x.intValue - y.doubleValue;
	else if (x.isInt == true && y.isBool == true) return x.intValue - y.boolValue;
	else if (x.isDouble == true && y.isInt == true) return x.doubleValue - y.intValue;
	else if (x.isDouble == true && y.isDouble == true) return x.doubleValue - y.doubleValue;
	else if (x.isDouble == true && y.isBool == true) return x.doubleValue - y.boolValue;
	else if (x.isBool == true && y.isInt == true) return x.boolValue - y.intValue;
	else if (x.isBool == true && y.isDouble == true) return x.boolValue - y.doubleValue;
	else if (x.isBool == true && y.isBool == true) return x.boolValue - y.boolValue;
	else if (x.isString == true && y.isInt == true) return x.stringValue - y.intValue;
	else if (x.isString == true && y.isBool == true) return x.stringValue - y.boolValue;
	return none;
};


val operator/ (val x, val y) {
	if (x.isInt == true && y.isInt == true) return x.intValue / y.intValue;
	else if (x.isInt == true && y.isDouble == true) return x.intValue / y.doubleValue;
	else if (x.isDouble == true && y.isInt == true) return x.doubleValue / y.intValue;
	else if (x.isDouble == true && y.isDouble == true) return x.doubleValue / y.doubleValue;
	return none;
};

val operator* (val x, val y) {
	if (x.isInt == true && y.isInt == true) return x.intValue * y.intValue;
	else if (x.isInt == true && y.isDouble == true) return x.intValue * y.doubleValue;
	else if (x.isInt == true && y.isBool == true) return x.intValue * y.boolValue;
	else if (x.isDouble == true && y.isInt == true) return x.doubleValue * y.intValue;
	else if (x.isDouble == true && y.isDouble == true) return x.doubleValue * y.doubleValue;
	else if (x.isDouble == true && y.isBool == true) return x.doubleValue * y.boolValue;
	else if (x.isBool == true && y.isInt == true) return x.boolValue * y.intValue;
	else if (x.isBool == true && y.isDouble == true) return x.boolValue * y.doubleValue;
	else if (x.isBool == true && y.isBool == true) return x.boolValue * y.boolValue;
	return none;
};

val operator% (val x, val y) {
	if (x.isInt == true && y.isInt == true) return x.intValue % y.intValue;
	return none;
};

bool operator== (val x, val y) {
	if (x.isInt == true && y.isInt == true) return (x.intValue == y.intValue);
	else if (x.isInt == true && y.isDouble == true) return (x.intValue == y.doubleValue);
	else if (x.isDouble == true && y.isInt == true) return (x.doubleValue == y.intValue);
	else if (x.isDouble == true && y.isDouble == true) return (x.doubleValue == y.doubleValue);
	else if (x.isBool == true && y.isBool == true) return (x.boolValue == y.boolValue);
	else if (x.isString == true && y.isString == true) return (x.stringValue == y.stringValue);
	return false;
}

bool operator!= (val x, val y) {
	if (x.isInt == true && y.isInt == true) return (x.intValue != y.intValue);
	else if (x.isInt == true && y.isDouble == true) return (x.intValue != y.doubleValue);
	else if (x.isDouble == true && y.isInt == true) return (x.doubleValue != y.intValue);
	else if (x.isDouble == true && y.isDouble == true) return (x.doubleValue != y.doubleValue);
	else if (x.isBool == true && y.isBool == true) return (x.boolValue != y.boolValue);
	else if (x.isString == true && y.isString == true) return (x.stringValue != y.stringValue);
	return false;
}
bool operator>= (val x, val y) {
	if (x.isInt == true && y.isInt == true) return (x.intValue >= y.intValue);
	else if (x.isInt == true && y.isDouble == true) return (x.intValue >= y.doubleValue);
	else if (x.isDouble == true && y.isInt == true) return (x.doubleValue >= y.intValue);
	else if (x.isDouble == true && y.isDouble == true) return (x.doubleValue >= y.doubleValue);
	else if (x.isBool == true && y.isBool == true) return (x.boolValue >= y.boolValue);
	else if (x.isString == true && y.isString == true) return (x.stringValue >= y.stringValue);
	return false;
}
bool operator<= (val x, val y) {
	if (x.isInt == true && y.isInt == true) return (x.intValue <= y.intValue);
	else if (x.isInt == true && y.isDouble == true) return (x.intValue <= y.doubleValue);
	else if (x.isDouble == true && y.isInt == true) return (x.doubleValue <= y.intValue);
	else if (x.isDouble == true && y.isDouble == true) return (x.doubleValue <= y.doubleValue);
	else if (x.isBool == true && y.isBool == true) return (x.boolValue <= y.boolValue);
	else if (x.isString == true && y.isString == true) return (x.stringValue <= y.stringValue);
	return false;
}

bool operator> (val x, val y) {
	if (x.isInt == true && y.isInt == true) return (x.intValue > y.intValue);
	else if (x.isInt == true && y.isDouble == true) return (x.intValue > y.doubleValue);
	else if (x.isDouble == true && y.isInt == true) return (x.doubleValue > y.intValue);
	else if (x.isDouble == true && y.isDouble == true) return (x.doubleValue > y.doubleValue);
	else if (x.isBool == true && y.isBool == true) return (x.boolValue > y.boolValue);
	else if (x.isString == true && y.isString == true) return (x.stringValue > y.stringValue);
	return false;
}
bool operator< (val x, val y) {
	if (x.isInt == true && y.isInt == true) return (x.intValue < y.intValue);
	else if (x.isInt == true && y.isDouble == true) return (x.intValue < y.doubleValue);
	else if (x.isDouble == true && y.isInt == true) return (x.doubleValue < y.intValue);
	else if (x.isDouble == true && y.isDouble == true) return (x.doubleValue < y.doubleValue);
	else if (x.isBool == true && y.isBool == true) return (x.boolValue < y.boolValue);
	else if (x.isString == true && y.isString == true) return (x.stringValue < y.stringValue);
	return false;
}

void change(val* MapValBuffer) {
	MapValBuffer->intValue = none;
	MapValBuffer->doubleValue = none;
	MapValBuffer->boolValue = none;
	MapValBuffer->stringValue = "";
	MapValBuffer->objectMap.clear();
	MapValBuffer->isInt = false;
	MapValBuffer->isDouble = false;
	MapValBuffer->isBool = false;
	MapValBuffer->isString = false;
	MapValBuffer->isObject = false;
	MapValBuffer->isFunc = false;
}

Map addToMap(Map map, string mapIndex, val value) {
	if (value.isInt == true) {
		map.insert(pair<string, val>(mapIndex, value.intValue));
	}
	else if (value.isDouble == true) {
		map.insert(pair<string, val>(mapIndex, value.doubleValue));
	}
	else if (value.isBool == true) {
		map.insert(pair<string, val>(mapIndex, value.boolValue));
	}
	else if (value.isString == true) {
		map.insert(pair<string, val>(mapIndex, value.stringValue));
	}
	else if (value.isObject == true) {
		map.insert(pair<string, val>(mapIndex, value.objectMap));
	}
	else if (value.isFunc == true) {
		map.insert(pair<string, val>(mapIndex, value.funcVal));
	}
	return map;
}

class vals {
public:
	Map BufferValsMap;
	int valsBufferMapIndex = 0;

	vals() {
	};

	vals(int i) {
	}

	vals operator, (val value) {
		BufferValsMap = addToMap(BufferValsMap, to_string(valsBufferMapIndex), value);
		valsBufferMapIndex++;
		vals temp(*this);
		return temp;
	}

	vals operator, (function <val()> value) {
		BufferValsMap = addToMap(BufferValsMap, to_string(valsBufferMapIndex), value);
		valsBufferMapIndex++;
		vals temp(*this);
		return temp;
	}

	/*friend vals operator, (val vals, Object object);*/
};

vals valsobj;

class key {
public:
	val value;
	string id;

	key() {}

	key(string id) {
		this->id = id;
	}

	key operator= (val value) {
		keyfuncBufferMap = addToMap(keyfuncBufferMap, this->id, value);
		key temp(*this);
		return temp;
	}

	key operator= (function <val()> value) {
		this->value.isFunc = true;
		this->value.funcVal = value;
		keyfuncBufferMap = addToMap(keyfuncBufferMap, this->id, value);
		key temp(*this);
		return temp;
	}

	key operator, (key nextkey) {
		addToMap(keyfuncBufferMap, nextkey.id, nextkey.value);
		key temp(*this);
		return temp;
	}

	key operator=(Object myobject);
};

class myCall {
public:
	string callid;
	bool shouldBeUsed = false;
	void operator() (string callid) {
		this->callid = callid;
		shouldBeUsed = true;
	}
};

myCall call;

class Object {
private:
public:
	Map ObjectValuesMap;
	bool receiving = false;
	Object* msgObject = nullptr;
	string callString = "";
	Object() {
	};
	Object operator[] (vals myvals) {
		Object temp;
		valsobj = myvals;
		temp.ObjectValuesMap = valsobj.BufferValsMap;
		valsobj.BufferValsMap.clear();
		valsobj.valsBufferMapIndex = 0;
		if (call.shouldBeUsed == true) {
			temp.callString = call.callid;
			call.shouldBeUsed = false;
		}
		return temp;
	}
	Object operator[] (key mykey) {
		Object temp;
		temp.ObjectValuesMap = keyfuncBufferMap;
		keyfuncBufferMap.clear();
		if (call.shouldBeUsed == true) {
			temp.callString = call.callid;
			call.shouldBeUsed = false;
		}
		return temp;
	}
	val operator[] (const char* mystr) {
		MapValBuffer = &((*this).ObjectValuesMap[mystr]);
		return (*this).ObjectValuesMap[mystr];
	}

	friend ostream& operator<< (ostream& os, Object myObject);
	void operator<<(Object msg_object);
};

Object object;
Object* receivingObject;

void Object::operator<< (Object msg_object) {
	receiving = true;
	msgObject = new Object;
	msgObject->ObjectValuesMap = msg_object.ObjectValuesMap;
	msgObject->callString = msg_object.callString;
	receivingObject = this;
	map<string, val>::iterator itr;
	itr = ObjectValuesMap.find(msgObject->callString);
	if (itr->second.isFunc == true) {
		itr->second.funcVal();
	}
}

key key::operator= (Object myobject) {
	val tempvalue(myobject.ObjectValuesMap);
	keyfuncBufferMap = addToMap(keyfuncBufferMap, this->id, tempvalue);
	return (*this);
}

vals operator, (vals myvals, Object object) {
	myvals.BufferValsMap = addToMap(myvals.BufferValsMap, to_string(myvals.valsBufferMapIndex), object.ObjectValuesMap);
	myvals.valsBufferMapIndex++;
	return myvals;
}

void val::operator= (Object myobject) {
	change(MapValBuffer);
	MapValBuffer->objectMap = myobject.ObjectValuesMap;
	MapValBuffer->isObject = true;
}

ostream& operator<<(ostream& os, Object myObject)
{
	if (!myObject.ObjectValuesMap.empty()) {
		os << "object [ ";
		map<string, val>::iterator itr;
		for (itr = myObject.ObjectValuesMap.begin(); itr != myObject.ObjectValuesMap.end(); ++itr) {
			os << "\"" << itr->first << "\"" << ":" << itr->second << " ";
			if (next(itr) != myObject.ObjectValuesMap.end()) {
				os << ", ";
			}
		}
		os << "]\n";
	}
	else {
		os << "Empty object\n";
	}
	return os;
}

bool isNumber(const string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}
bool is_number(const std::string& s)
{
	long double ld;
	return((std::istringstream(s) >> ld >> std::ws).eof());
}

char* convertTochar(string a) {
	size_t i;
	size_t size = a.size();
	char* s = new char[size];
	for (i = 0; i < size; i++) {
		s[i] = a[i];
	}
	s[i] = '\0';
	return s;
}

class MyInput {
private:
public:
	MyInput() {};
	val operator() (string msg) {
		val dt;
		string str_de;

		cout << msg;
		cin >> str_de;

		if (isNumber(str_de) == true) {
			dt.isInt = true;
			dt.intValue = stoi(str_de);
		}
		else if (is_number(str_de) == true) {
			dt.isDouble = true;
			dt.doubleValue = stod(str_de);
		}
		else if (str_de.compare("true") == 0) {
			dt.isBool = true;
			dt.boolValue = true;
		}
		else if (str_de.compare("false") == 0) {
			dt.isBool = true;
			dt.boolValue = false;
		}
		else {
			dt.isString = true;
			dt.stringValue = convertTochar(str_de);
		}
		return dt;
	}
};

MyInput input;

class MyRef {
private:
public:
	MyRef() {};
	Object& operator() (Object& ref_object) {
		return ref_object;
	}
};
MyRef refa;

ostream& operator<<(ostream& os, val myValue)
{
	if (myValue.isInt == true) {
		os << myValue.intValue;
	}
	else if (myValue.isDouble == true) {
		os << myValue.doubleValue;
	}
	else if (myValue.isString == true) {
		os << '"' << myValue.stringValue << '"';
	}
	else if (myValue.isBool == true) {
		if (myValue.boolValue == false) {
			os << "false";
		}
		else {
			os << "true";
		}
	}
	else if (myValue.isFunc == true) {
		os << "method";
	}
	else if (myValue.isObject == true) {
		if (!myValue.objectMap.empty()) {
			os << "object [ ";
			map<string, val>::iterator itr;
			for (itr = myValue.objectMap.begin(); itr != myValue.objectMap.end(); ++itr) {
				os << "\"" << itr->first << "\"" << ":" << itr->second << " ";
				if (next(itr) != myValue.objectMap.end()) {
					os << ", ";
				}
			}
			os << "]";
		}
		else {
			os << "Empty object";
		}
	}
	return os;
}

val self(val i) {
	string keyid;
	if (i.isInt) {
		keyid = to_string(i.intValue);
	}
	else if (i.isDouble) {
		keyid = to_string(i.doubleValue);
	}
	else if (i.isString) {
		keyid = i.stringValue;
	}
	else {
		cout << "Error, object does not have the key with this id or the id is of invalid format\n";
		return 0;
	}
	map <string, val>::iterator itr;
	itr = receivingObject->ObjectValuesMap.find(keyid);
	return itr->second;
}

val arg(val i) {
	string keyid;
	if (i.isInt) {
		keyid = to_string(i.intValue);
	}
	else if (i.isDouble) {
		keyid = to_string(i.doubleValue);
	}
	else if (i.isString) {
		keyid = i.stringValue;
	}
	else {
		cout << "Error, object does not have the key with this id or the id is of invalid format\n";
		return 0;
	}
	map <string, val>::iterator itr;
	itr = receivingObject->msgObject->ObjectValuesMap.find(keyid);
	return itr->second;
}

void eval(string keyid) {
	map <string, val>::iterator itr;
	itr = receivingObject->msgObject->ObjectValuesMap.find(keyid);
	if (itr->second.isFunc == true) {
		itr->second.funcVal();
	}
}

bool eval_cond(string keyid) {
	map <string, val>::iterator itr;
	itr = receivingObject->msgObject->ObjectValuesMap.find(keyid);
	if (itr->second.isFunc == true) {
		if (itr->second.funcVal().isBool) {
			return itr->second.funcVal().boolValue;
		}
	}
	return false;
}

list<val> argumentList() {
	list<val> my_vals;
	transform(receivingObject->msgObject->ObjectValuesMap.begin(), receivingObject->msgObject->ObjectValuesMap.end(), back_inserter(my_vals), [](const Map::value_type& val) {return val.second; });
	return my_vals;
}
#pragma once
