int get_Value(struct KeyVal table[], int table_count, char *key) {
  for (int i = 0; i < table_count; i++) { // check for /r
    if (strcmp(table[i].key, key) == 0) {
      return table[i].value;
    }
  }

  return -1;
}
