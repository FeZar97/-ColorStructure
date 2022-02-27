#include <sstream>
#include "gtest/gtest.h"
#include "ColorSequence.h"

namespace ColorSetTest {

	class ColorSetTest : public ::testing::Test
	{
	protected:
		void SetUp() override 
		{
			redColorSet = { Color::Red, 1, 5 };
			greenColorSet = { Color::Green, 6, 5 };
			blueColorSet = { Color::Blue, 11, 5 };
			anotherRedColorSet = { Color::Red, 6, 5 };
		}

		ColorSet redColorSet, greenColorSet, blueColorSet;
		ColorSet anotherRedColorSet;
	};

	TEST_F(ColorSetTest, DefaultCtorTest)
	{
		ColorSet defaultColorSet;
		EXPECT_EQ(defaultColorSet.color(), Color::Red);
		EXPECT_EQ(defaultColorSet.startNumber(), 1);
		EXPECT_EQ(defaultColorSet.size(), 1);
	}

	TEST_F(ColorSetTest, CtorTest) 
	{
		EXPECT_EQ(redColorSet.color(), Color::Red);
		EXPECT_EQ(redColorSet.startNumber(), 1);
		EXPECT_EQ(redColorSet.size(), 5);
	}

	TEST_F(ColorSetTest, EqualOperatorTest1) 
	{
		ASSERT_TRUE(redColorSet == redColorSet);
	}

	TEST_F(ColorSetTest, EqualOperatorTest2) 
	{
		ASSERT_TRUE(redColorSet != greenColorSet);
	}

	TEST_F(ColorSetTest, EqualOperatorTest3) 
	{
		ASSERT_TRUE(redColorSet != anotherRedColorSet);
	}

	TEST_F(ColorSetTest, CorrectMergeTest) 
	{
		redColorSet.merge(anotherRedColorSet);
		ASSERT_TRUE(redColorSet == ColorSet(Color::Red, 1, 10));
	}

	TEST_F(ColorSetTest, IncorrectMergeTest) 
	{
		redColorSet.merge(blueColorSet);
		ASSERT_TRUE(redColorSet == ColorSet(Color::Red, 1, 5));
	}

	TEST_F(ColorSetTest, RecolorResultTest1) 
	{
		size_t digitsToRecolor = 3, initialDigitsNb = greenColorSet.size(), startNumber = greenColorSet.startNumber();
		const auto recolorResult = ColorSet::getRecolorResult(Color::Green, Color::Blue, digitsToRecolor, greenColorSet);

		ASSERT_TRUE(recolorResult.first.has_value());
		ASSERT_TRUE(recolorResult.second.has_value());
		ASSERT_TRUE(*recolorResult.first == ColorSet(Color::Blue, startNumber, digitsToRecolor));
		ASSERT_TRUE(*recolorResult.second ==
			ColorSet(Color::Green, startNumber + digitsToRecolor, greenColorSet.size() - digitsToRecolor));
	}

	TEST_F(ColorSetTest, RecolorResultTest2) 
	{
		size_t digitsToRecolor = 9, initialDigitsNb = greenColorSet.size();
		const auto recolorResult = ColorSet::getRecolorResult(Color::Green, Color::Blue, digitsToRecolor, greenColorSet);

		ASSERT_TRUE(recolorResult.first.has_value());
		ASSERT_TRUE(!recolorResult.second.has_value());
		ASSERT_TRUE(*recolorResult.first == ColorSet(Color::Blue, greenColorSet.startNumber(), greenColorSet.size()));
	}

	TEST_F(ColorSetTest, RecolorResultTest3) 
	{
		const auto recolorResult = ColorSet::getRecolorResult(Color::Red, Color::Blue, redColorSet.size(), redColorSet);

		ASSERT_TRUE(!recolorResult.first.has_value());
		ASSERT_TRUE(!recolorResult.second.has_value());
	}

	TEST_F(ColorSetTest, RecolorResultTest4) 
	{
		const auto recolorResult = ColorSet::getRecolorResult(Color::Green, Color::Blue, redColorSet.size(), redColorSet);

		ASSERT_TRUE(!recolorResult.first.has_value());
		ASSERT_TRUE(!recolorResult.second.has_value());
	}

} // namespace ColorSetTest


namespace ColorSequenceTest {

	class ColorSequenceTest : public ::testing::Test
	{
	protected:
		const static size_t cDefaultEndDigit = 5;

		void SetUp() override 
		{
			osstream.flush();
			redSequence = { cDefaultStartNumber, cDefaultEndDigit, Color::Red };
			greenSequence = { cDefaultStartNumber, cDefaultEndDigit, Color::Green };
			blueSequence = { cDefaultStartNumber, cDefaultEndDigit, Color::Blue };
		}

		std::ostringstream osstream;
		ColorSequence redSequence, greenSequence, blueSequence;
	};

	TEST_F(ColorSequenceTest, DefaultCtorTest)
	{
		osstream << ColorSequence();
		EXPECT_EQ(osstream.str(), "1r");
	}

	TEST_F(ColorSequenceTest, CtorTest)
	{
		osstream << redSequence;
		EXPECT_EQ(osstream.str(), "1r2r3r4r5r");
	}

	TEST_F(ColorSequenceTest, IncorrecRecolorTest1)
	{
		EXPECT_EQ(ColorSequence::UNAVALAIBLE_COLOR_PAIR,
			redSequence.recolor(Color::Red, Color::Blue, cDefaultEndDigit));
		osstream << redSequence;
		EXPECT_EQ(osstream.str(), "1r2r3r4r5r");
	}

	TEST_F(ColorSequenceTest, IncorrecRecolorTest2)
	{
		EXPECT_EQ(ColorSequence::INVALID_DIGITS_ARG,
			greenSequence.recolor(Color::Green, Color::Blue, -1));
		osstream << greenSequence;
		EXPECT_EQ(osstream.str(), "1g2g3g4g5g");
	}

	TEST_F(ColorSequenceTest, IncorrecRecolorTest3)
	{
		EXPECT_EQ(ColorSequence::NOTHING_TO_RECOLOR,
			redSequence.recolor(Color::Green, Color::Blue, cDefaultEndDigit));
		osstream << redSequence;
		EXPECT_EQ(osstream.str(), "1r2r3r4r5r");
	}

	TEST_F(ColorSequenceTest, EmptyRecolorTest)
	{
		EXPECT_EQ(ColorSequence::SUCCESS,
			greenSequence.recolor(Color::Green, Color::Blue, 0));
		osstream << greenSequence;
		EXPECT_EQ(osstream.str(), "1g2g3g4g5g");
	}

	TEST_F(ColorSequenceTest, FullRecolorTest)
	{
		EXPECT_EQ(ColorSequence::SUCCESS,
			greenSequence.recolor(Color::Green, Color::Blue, cDefaultEndDigit));
		osstream << greenSequence;
		EXPECT_EQ(osstream.str(), "1b2b3b4b5b");
	}

	TEST_F(ColorSequenceTest, PartRecolorTest)
	{
		EXPECT_EQ(ColorSequence::SUCCESS,
			greenSequence.recolor(Color::Green, Color::Blue, 3));
		osstream << greenSequence;
		EXPECT_EQ(osstream.str(), "1b2b3b4g5g");
	}

	TEST_F(ColorSequenceTest, ExampleRecolorTest)
	{
		struct RecolorParams
		{
			Color src, dst;
			int digitsToRecolor, recolorResult;
			std::string result;
		};
		const std::vector<RecolorParams> cRecolorParamsArray = {
			{Color::Green, Color::Blue,  3, ColorSequence::SUCCESS, "1b2b3b4g5g6g7g8g9g"},
			{Color::Green, Color::Blue,  3, ColorSequence::SUCCESS, "1b2b3b4b5b6b7g8g9g"},
			{Color::Red,   Color::Blue,  3, ColorSequence::UNAVALAIBLE_COLOR_PAIR, 
																	"1b2b3b4b5b6b7g8g9g"},
			{Color::Blue,  Color::Red,   9, ColorSequence::SUCCESS, "1r2r3r4r5r6r7g8g9g"},
			{Color::Green, Color::Blue,  9, ColorSequence::SUCCESS, "1r2r3r4r5r6r7b8b9b"},
			{Color::Blue,  Color::Green, 2, ColorSequence::SUCCESS, "1r2r3r4r5r6r7g8g9b"}
		};

		ColorSequence sequence(1, 9, Color::Green);

		for (const RecolorParams& params : cRecolorParamsArray)
		{
			std::ostringstream osstream;
			EXPECT_EQ(params.recolorResult, sequence.recolor(params.src, params.dst, params.digitsToRecolor));
			osstream << sequence;
			EXPECT_EQ(osstream.str(), params.result);
		}
	}

} // namespace ColorSequenceTest


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}