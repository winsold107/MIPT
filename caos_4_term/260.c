#include <openssl/sha.h>
#include <stdio.h>
#include <unistd.h>

int main() {
		SHA512_CTX ctx;
		SHA512_Init(&ctx);
		char buffer[64];
		size_t read_len;
		while((read_len = read(0, buffer, sizeof(buffer))) > 0) {
				SHA512_Update(&ctx, buffer, read_len);
		}
		char hash[64];
		SHA512_Final(hash, &ctx);
		printf("0x");
		for(int i = 0; i < sizeof(hash); i++) {
				printf("%02x", hash[i] & 0xff);
		}
		return 0;
}
