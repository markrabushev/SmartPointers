#include <iostream>
#include "CTrace.h"
#include "Smart_shared_ptr.h"
#include "Smart_weak_ptr.h"


void shared_demonstration()
{
	std::cout << "smart_shared_ptr"  << std::endl << std::endl;

	smart_shared_ptr<CTrace> ssp0(); // конструктор по умолчанию
	smart_shared_ptr<CTrace> ssp1(new CTrace(6)); // конструктор с параметром
	smart_shared_ptr<CTrace> ssp2(ssp1); // copy-конструктор

	std::cout << "ssp1 Value: " << *ssp1 << " Count: " << ssp1.use_count() << std::endl;
	std::cout << "ssp2 Value: " << *ssp2 << " Count: " << ssp2.use_count() << std::endl << std::endl;

	smart_shared_ptr<CTrace> ssp3(std::move(ssp1)); // move-конструктор

	std::cout << "ssp2 Value: " << *ssp2 << " Count: " << ssp2.use_count() << std::endl;
	std::cout << "ssp3 Value: " << *ssp3 << " Count: " << ssp3.use_count() << std::endl << std::endl;

	ssp1 = ssp3; // copy-оператор присваивания

	std::cout << "ssp1 Value: " << *ssp1 << " Count: " << ssp1.use_count() << std::endl;
	std::cout << "ssp2 Value: " << *ssp2 << " Count: " << ssp2.use_count() << std::endl;
	std::cout << "ssp3 Value: " << *ssp3 << " Count: " << ssp3.use_count() << std::endl << std::endl;

	ssp1 = std::move(ssp3); // move-оператор присваивания
	
	std::cout << "ssp1 Value: " << *ssp1 << " Count: " << ssp1.use_count() << std::endl;
	std::cout << "ssp2 Value: " << *ssp2 << " Count: " << ssp2.use_count() << std::endl << std::endl;

	if (ssp1.get() == ssp2.get()) std::cout << "ssp1 == ssp2" << std::endl;
	if (ssp1) std::cout << "ssp1 != null" << std::endl;
	ssp1.reset();
	if (!ssp1) std::cout << "ssp1 == null" << std::endl;
}

void weak_demonstration()
{
	std::cout << "smart_weak_ptr" << std::endl << std::endl;
	smart_shared_ptr<CTrace> shared(new CTrace(3));
	smart_weak_ptr<CTrace> weak(shared);
	smart_shared_ptr<CTrace> shared2 = weak.lock();
	if (shared2) {
		std::cout << "weak_ptr is valid. Value: " << shared2->m_a << std::endl;
	}
	else {
		std::cout << "weak_ptr is expired." << std::endl;
	}

	shared.reset();

	smart_shared_ptr<CTrace> shared3 = weak.lock();
	if (shared3) {
		std::cout << "weak_ptr is valid. Value: " << shared3->m_a << std::endl;
	}
	else {
		std::cout << "weak_ptr is expired." << std::endl;
	}


	std::shared_ptr<CTrace> std_shared(new CTrace(5));
	std::weak_ptr<CTrace> std_weak(std_shared);
	std::shared_ptr<CTrace> std_shared2 = std_weak.lock();
	if (std_shared2) {
		std::cout << "weak_ptr is valid. Value: " << std_shared2->m_a << std::endl;
	}
	else {
		std::cout << "weak_ptr is expired." << std::endl;
	}

	std_shared.reset();

	std::shared_ptr<CTrace> std_shared3 = std_weak.lock();
	if (std_shared3) {
		std::cout << "weak_ptr is valid. Value: " << std_shared3->m_a << std::endl;
	}
	else {
		std::cout << "weak_ptr is expired." << std::endl;
	}
}
int a = 5;
int main()
{
	shared_demonstration();
	weak_demonstration();
}