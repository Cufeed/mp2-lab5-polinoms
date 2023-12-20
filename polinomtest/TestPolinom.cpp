#include "TPolinom.h"
#include <gtest.h>

TEST(Polinom, Created_polinom_is_empty) {
	TPolinom polinom;
	EXPECT_TRUE(polinom.IsEmpty());
}

TEST(Polinom, Created_polinom_with_one_monom_is_not_empty) {
	TPolinom polinom;
	TMonom monom(2.5, 1, 2, 3);
	polinom.AddMonom(monom);
	EXPECT_FALSE(polinom.IsEmpty());
}

TEST(Polinom, Coefficients_add_up_if_degrees_are_equal) {
	TPolinom polinom;
	TMonom monom1(2.5, 1, 2, 3);
	TMonom monom2(3.7, 1, 2, 3);
	polinom.AddMonom(monom1);
	cout << polinom.ToString() << endl;
	polinom.AddMonom(monom2);
	cout << polinom.ToString() << endl;
	polinom.ToCreed();
	std::cout << "Coefficient: " << polinom.GetCurrentItem().GetCoef() << std::endl;
	std::cout << "Length: " << polinom.GetLength() << std::endl;
	EXPECT_EQ(polinom.GetLength(), 1);
	EXPECT_EQ(polinom.GetCurrentItem().GetCoef(), 6.2);
}

TEST(Polinom, Coefficients_dont_add_up_if_degrees_are_different) {
	TPolinom polinom;
	TMonom monom1(2.5, 1, 2, 3);
	TMonom monom2(3.7, 2, 3, 4);
	polinom.AddMonom(monom1);
	cout << polinom.ToString() << endl;
	polinom.AddMonom(monom2);
	cout << polinom.ToString() << endl;
	cout << polinom.GetLength() << endl;
	cout << "Expect: 2" << endl;
	EXPECT_EQ(polinom.GetLength(), 2);
}

TEST(Polinom, Monom_delete_if_coefficient_equal_zero) {
	TPolinom polinom;
	TMonom monom1(0, 1, 2, 3);
	polinom.AddMonom(monom1);
	EXPECT_EQ(polinom.GetLength(), 0);
}

TEST(Polinom, Can_not_get_monom_from_empty_polinom) {
	TPolinom polinom;
	EXPECT_THROW(polinom.GetCurrentItem(), std::out_of_range);
}
