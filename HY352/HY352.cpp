#include "MSGlang.h"


int main() {


	/*let o0 = object[
		key("hhh") = 3, key("4") = 3, key("asd") = "c", key("bab") = true, key("babab") = false, key("a") = lambda{ return "ababab"; }, key("b") = lambda{ return 1; }, key("c") = lambda{ return 1.2; }, key("d") = lambda{ return false; }, key("thisistheobject") = object[values 2, "s"], key("thisistheobject2") = object[values 2, "aga"]
	];
	let o1 = object[values 2, 3.2, "a", true, false, lambda{ return "ababab"; }, lambda{ return 1; }, lambda{ return "A"; }, lambda{ return false; }, lambda{ return true; }];

	let o2 = object[values 4, 3, 3, "3"];

	let o3 = object[
		key("hhh") = 3, key("4") = 3, key("asd") = "c", key("bab") = true, key("babab") = false, key("a") = lambda{ return "ababab"; }, key("b") = lambda{ return 1; }, key("c") = lambda{ return 1.2; }, key("d") = lambda{ return false; }, func("myfunc") { return "bab"; }
	];

	let o4 = object[values object[values 5, "x", false, true, 5.5],
		object[
			key("hhh") = 3, key("4") = 3, key("asd") = "c", key("bab") = true, key("babab") = false, key("a") = lambda{ return self(3); }, key("b") = lambda{ return 1; }, key("c") = lambda{ return 1.2; }, key("d") = lambda{ return false; }
		],
		3, 2.3, o2, "a", lambda{ return "ababab"; }];

	o2["3"] = input("x:");
	cout << o2["3"] << nl;
	cout << input("x:") << nl;
	o2["1"] = 0;
	o2["2"] = false;
	cout << o2;


	cout << o1;
	cout << o2;
	cout << o3;
	cout << o4;
	
	let printf_impl = object[
		key("4") = "abab",
		key("2") = 4,
		key("3") = 6,
		func("printf") {
			cout << arg("a") + self(2) << nl;
			if (eval_cond("falsefunc")) {
				eval("showme");
				eval("equal");
			}
			return none;
		}
	];

	let callerobject = object[
		call("printf"),
		func("showme") {
			cout << "this is bab\n";
			return none;
		}, 
		func("falsefunc"){
			return true;
		},
		func("equal") {
			if (self("3") == arg("3")) {
				cout << "same\n";
			}
			else {
				cout << "different\n";
			}
			return none;
		},
		key("a") = 5,
		key("3") = 6
	];
	
	printf_impl << callerobject;

	let printf_implement = object[
		func("printf") {
			for (auto& v : args_list)
				std::cout << v << nl;
			return none;
		}
	];

	let callerobjectimplement = object[call("printf"), values 1, "2", true, -3.14];

	printf_implement << callerobjectimplement;*/

	let o1 = object;
	let o2 = object[values 1, "5", true, false, 3.2, object[values 3, 2]];
	let o3 = object[
		key("a") = 3,
		key("b") = "asd",
		key("c") = lambda{ return none; },
		func("d") { return none; }
	];

	cout << o1 << nl << o2 << nl << o3 << nl;

	let o4 = object[values 1, 2, ref(o3)];
	cout << o4;

	let printf_impl = object[
		key("4") = "abab",
		key("2") = 4,
		key("3") = 6,
		func("printf") {
			cout << arg("a") + self(2) << nl;
			if (eval_cond("falsefunc")) {
				eval("showme");
				eval("equal");
			}
			return none;
		}
	];

	let callerobject = object[
		call("printf"),
			func("showme") {
			cout << "this is bab\n";
			return none;
		},
			func("falsefunc"){
			return 1==1;
		},
			func("equal") {
			if (self("3") == arg("3")) {
				cout << "same\n";
			}
			else {
				cout << "different\n";
			}
			return none;
		},
			key("a") = 5,
			key("3") = 8
	];

	printf_impl << callerobject;

	let printf_implement = object[
		func("printf") {
			for (auto& v : args_list)
				cout << v << nl;
			return none;
		}
	];

	let callerobjectimplement = object[call("printf"), values 1, "2", true, -3.14];

	printf_implement << callerobjectimplement;

	return 0;
}