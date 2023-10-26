void main() {
    char* videoMem = (char*) 0xb8000;
    *(videoMem + 0) = 'k';
    *(videoMem + 2) = 'e';
    *(videoMem + 4) = 'r';
    *(videoMem + 6) = 'n';
    *(videoMem + 8) = '.';
}