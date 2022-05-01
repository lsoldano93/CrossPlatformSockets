#include <gtest/gtest.h>

#include "IpV4Address.hpp"

using namespace CrossPlatformSockets;

namespace 
{
   constexpr uint32_t LINK_LOCAL_ADDR = 2130706433;
}

TEST(IpV4Address, ByStringConstruction) 
{
   auto address = IpV4Address::create("127.0.0.1");
   ASSERT_TRUE(address.has_value());
   EXPECT_EQ(LINK_LOCAL_ADDR, address->get_address());
   EXPECT_EQ("127.0.0.1", address->to_string());
}

TEST(IpV4Address, ByStringConstruction_Invalid) 
{
   auto address1 = IpV4Address::create("asdasdasdasd");
   EXPECT_FALSE(address1.has_value());

   auto address2 = IpV4Address::create("3000000000000000");
   EXPECT_FALSE(address2.has_value());

   auto address3 = IpV4Address::create("299.255.124.0");
   EXPECT_FALSE(address3.has_value());
}

TEST(IpV4Address, ByOctetConstruction) 
{
   auto address = IpV4Address::create(127, 0, 0, 1);
   ASSERT_TRUE(address.has_value());
   EXPECT_EQ(LINK_LOCAL_ADDR, address->get_address());
   EXPECT_EQ("127.0.0.1", address->to_string());
}

TEST(IpV4Address, ByAddressConstruction) 
{
   auto address = IpV4Address::create(LINK_LOCAL_ADDR);
   ASSERT_TRUE(address.has_value());
   EXPECT_EQ(LINK_LOCAL_ADDR, address->get_address());
   EXPECT_EQ("127.0.0.1", address->to_string());
}

TEST(IpV4Address, StreamOperator)
{
   auto address = IpV4Address::create(LINK_LOCAL_ADDR);
   ASSERT_TRUE(address.has_value());
   std::ostringstream os;
   os << *address;
   EXPECT_EQ("127.0.0.1", os.str());
}
