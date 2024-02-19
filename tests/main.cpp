#include <aes.hpp>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>
#include <chrono>
#include "base64.hpp"

std::string aes_ecs_encrypt_pkcs7(std::string_view data, const std::uint8_t* key) {
  const size_t padding = 16 - (data.length() % 16);
  const size_t result_length = data.length() + padding;
  
  std::string result;
  result.resize(result_length);
  std::memcpy(result.data(), data.data(), data.length());
  std::memset(&result[data.length()], static_cast<int>(padding), padding);

  AES_ctx ctx;
  AES_init_ctx(&ctx, key);

  for (size_t i = 0; i < result_length; i += 16) {
    AES_ECB_encrypt(&ctx, reinterpret_cast<std::uint8_t*>(&result[i])); 
  }

  return result;
}

void print_hex(std::string_view encrypted) {
  std::cout << std::hex;
  for (size_t i = 0; i < encrypted.length(); ++i) {
    if (i > 0 && i % 16 == 0) std::cout << '\n';
    std::cout << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(encrypted[i])) << ", ";
  };
  std::cout << std::endl;
}

void check(std::string_view input) {
  static const std::uint8_t key[32] {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
  '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' };

  std::cout << "Input: " << input << '\n';
  const auto now = std::chrono::high_resolution_clock::now();
  const auto result = aes_ecs_encrypt_pkcs7(input, key);
  std::cout << std::dec << std::chrono::duration_cast<
    std::chrono::microseconds
    >(std::chrono::high_resolution_clock::now() - now).count() << std::endl;
  
  // print_hex(result);
}

int main (int /* argc */, char** /* *argv[] */) {
  std::ios::sync_with_stdio(false);

  check("Hello World 123");   // 15
  check("Hello World 1234");  // 16
  check("Hello World 12345"); // 17
  check("Hello World 12345fddsffgdjfghejrtejncverjvnerdfgjdfngjdfngjdgndfngdgndfjnndfvndfnvdfueieirfnerfneruifnn"
      "dfdfdfdfdfnmnemnremrnernejrnejrnejrnejrnejrnerjnrjendsfdsfsdfdsfksjfdshfjhdsjfhwjfhwuiefhdsjbnfdsbfdsjfs"
      "ncvvncjvnjdvnduknu23nunewufnewukfnewukfnewukfnewdsfkjsdkmdvkvndsfkvnfjvndfjvnekfwjiejwrwiejrewierukfnkfnw"); 
  
    // std::cout << boost::beast::detail::base64_encode(encrypted) << std::endl;
  
 
  return 0;
} 


