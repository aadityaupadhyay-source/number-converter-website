#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void strrev(char* str) {
    int i = 0, j = strlen(str) - 1;
    while (i < j) {
        char temp = str[i];
        str[i++] = str[j];
        str[j--] = temp;
    }
}

void decimalToBinary(int decimal, char* output) {
    int i = 0;
    if (decimal == 0) {
        output[i++] = '0';
    }
    while (decimal > 0) {
        output[i++] = '0' + (decimal % 2);
        decimal /= 2;
    }
    output[i] = '\0';
    strrev(output);
}

void decimalToOctal(int decimal, char* output) {
    sprintf(output, "%o", decimal);
}

void decimalToHex(int decimal, char* output) {
    sprintf(output, "%X", decimal);
}

int binaryToDecimal(char* binary) {
    int decimal = 0;
    int length = strlen(binary);
    for (int i = 0; i < length; i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    return decimal;
}

int octalToDecimal(char* octal) {
    int decimal = 0;
    int length = strlen(octal);
    for (int i = 0; i < length; i++) {
        decimal = decimal * 8 + (octal[i] - '0');
    }
    return decimal;
}

int hexToDecimal(char* hex) {
    return (int)strtol(hex, NULL, 16);
}

int isValidBinary(const char* str) {
    while (*str) {
        if (*str != '0' && *str != '1') return 0;
        str++;
    }
    return 1;
}

int isValidOctal(const char* str) {
    while (*str) {
        if (*str < '0' || *str > '7') return 0;
        str++;
    }
    return 1;
}

int isValidHex(const char* str) {
    while (*str) {
        if (!isxdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int main() {
    char *contentLength;
    char *postData;
    int length = 0;
    
    // Print HTTP header
    printf("Content-Type: text/html\n\n");
    
    // Print HTML start
    printf("<!DOCTYPE html>\n");
    printf("<html><head>\n");
    printf("<title>Number Conversion Result</title>\n");
    printf("<style>\n");
    printf("@import url('https://fonts.googleapis.com/css2?family=Poppins:wght@400;600&display=swap');\n");
    printf("body { font-family: 'Poppins', sans-serif; margin: 0; padding: 40px; background: linear-gradient(135deg, #3a6186, #89253e); min-height: 100vh; }\n");
    printf(".container { background: white; padding: 40px; border-radius: 15px; max-width: 600px; margin: 0 auto; box-shadow: 0 20px 40px rgba(0,0,0,0.15); }\n");
    printf(".result { background: linear-gradient(135deg, #e8f5e8, #c8e6c9); padding: 25px; border-left: 5px solid #4caf50; margin: 20px 0; border-radius: 10px; }\n");
    printf(".error { background: linear-gradient(135deg, #ffebee, #ffcdd2); padding: 25px; border-left: 5px solid #f44336; margin: 20px 0; border-radius: 10px; }\n");
    printf("h1 { color: #333; text-align: center; font-weight: 600; }\n");
    printf("h3 { color: #2e7d32; margin-bottom: 15px; }\n");
    printf("p { margin: 8px 0; font-size: 16px; }\n");
    printf(".back-btn { display: inline-block; background: linear-gradient(135deg, #ff5722, #ff7043); color: white; padding: 12px 30px; text-decoration: none; border-radius: 25px; font-weight: 600; margin-top: 20px; transition: all 0.3s ease; }\n");
    printf(".back-btn:hover { background: linear-gradient(135deg, #e64a19, #d84315); transform: translateY(-2px); box-shadow: 0 8px 15px rgba(230,74,25,0.4); }\n");
    printf("</style>\n");
    printf("</head><body>\n");
    printf("<div class='container'>\n");
    printf("<h1>🔢 Number Conversion Result</h1>\n");
    
    // Get POST data length
    contentLength = getenv("CONTENT_LENGTH");
    if (contentLength != NULL) {
        length = atoi(contentLength);
    }
    
    if (length > 0) {
        // Allocate memory for POST data
        postData = (char*)malloc(length + 1);
        // Read POST data
        fgets(postData, length + 1, stdin);
        
        // Parse the form data
        char conversionType[20] = "";
        char inputValue[100] = "";
        
        // Simple parsing for form data like: conversion=dec2bin&input=123
        char* token = strtok(postData, "&");
        while (token != NULL) {
            if (strncmp(token, "conversion=", 11) == 0) {
                strcpy(conversionType, token + 11);
            } else if (strncmp(token, "input=", 6) == 0) {
                strcpy(inputValue, token + 6);
            }
            token = strtok(NULL, "&");
        }
        
        // Process conversion based on type
        if (strlen(conversionType) > 0 && strlen(inputValue) > 0) {
            printf("<div class='result'>\n");
            
            if (strcmp(conversionType, "dec2bin") == 0) {
                int decimal = atoi(inputValue);
                char binary[33];
                decimalToBinary(decimal, binary);
                printf("<h3>✅ Decimal to Binary Conversion</h3>\n");
                printf("<p><strong>Input (Decimal):</strong> %d</p>\n", decimal);
                printf("<p><strong>Output (Binary):</strong> %s</p>\n", binary);
                
            } else if (strcmp(conversionType, "bin2dec") == 0) {
                if (isValidBinary(inputValue)) {
                    int decimal = binaryToDecimal(inputValue);
                    printf("<h3>✅ Binary to Decimal Conversion</h3>\n");
                    printf("<p><strong>Input (Binary):</strong> %s</p>\n", inputValue);
                    printf("<p><strong>Output (Decimal):</strong> %d</p>\n", decimal);
                } else {
                    printf("</div><div class='error'>\n");
                    printf("<h3>❌ Error</h3>\n");
                    printf("<p>Invalid binary number. Please enter only 0s and 1s.</p>\n");
                }
                
            } else if (strcmp(conversionType, "dec2oct") == 0) {
                int decimal = atoi(inputValue);
                char octal[12];
                decimalToOctal(decimal, octal);
                printf("<h3>✅ Decimal to Octal Conversion</h3>\n");
                printf("<p><strong>Input (Decimal):</strong> %d</p>\n", decimal);
                printf("<p><strong>Output (Octal):</strong> %s</p>\n", octal);
                
            } else if (strcmp(conversionType, "oct2dec") == 0) {
                if (isValidOctal(inputValue)) {
                    int decimal = octalToDecimal(inputValue);
                    printf("<h3>✅ Octal to Decimal Conversion</h3>\n");
                    printf("<p><strong>Input (Octal):</strong> %s</p>\n", inputValue);
                    printf("<p><strong>Output (Decimal):</strong> %d</p>\n", decimal);
                } else {
                    printf("</div><div class='error'>\n");
                    printf("<h3>❌ Error</h3>\n");
                    printf("<p>Invalid octal number. Please enter digits 0-7 only.</p>\n");
                }
                
            } else if (strcmp(conversionType, "dec2hex") == 0) {
                int decimal = atoi(inputValue);
                char hex[12];
                decimalToHex(decimal, hex);
                printf("<h3>✅ Decimal to Hexadecimal Conversion</h3>\n");
                printf("<p><strong>Input (Decimal):</strong> %d</p>\n", decimal);
                printf("<p><strong>Output (Hexadecimal):</strong> %s</p>\n", hex);
                
            } else if (strcmp(conversionType, "hex2dec") == 0) {
                if (isValidHex(inputValue)) {
                    int decimal = hexToDecimal(inputValue);
                    printf("<h3>✅ Hexadecimal to Decimal Conversion</h3>\n");
                    printf("<p><strong>Input (Hexadecimal):</strong> %s</p>\n", inputValue);
                    printf("<p><strong>Output (Decimal):</strong> %d</p>\n", decimal);
                } else {
                    printf("</div><div class='error'>\n");
                    printf("<h3>❌ Error</h3>\n");
                    printf("<p>Invalid hexadecimal number. Please enter valid hex digits (0-9, A-F).</p>\n");
                }
            }
            printf("</div>\n");
        } else {
            printf("<div class='error'>\n");
            printf("<h3>❌ Error</h3>\n");
            printf("<p>Missing conversion type or input value.</p>\n");
            printf("</div>\n");
        }
        
        free(postData);
    } else {
        printf("<div class='error'>\n");
        printf("<h3>❌ Error</h3>\n");
        printf("<p>No data received.</p>\n");
        printf("</div>\n");
    }
    
    printf("<p><a href='/converter.html' class='back-btn'>← Back to Converter</a></p>\n");
    printf("</div></body></html>\n");
    
    return 0;
}
