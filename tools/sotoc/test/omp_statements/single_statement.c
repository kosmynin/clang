// RUN: %sotoc-transform-compile

int main(void) {
  int h = 0;

  #pragma omp target device(0)
  h += 1;


  return 0;
}
