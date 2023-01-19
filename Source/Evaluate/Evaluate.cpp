// ===--- Evaluate.cpp ------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The implementation for assertion expression evaluation.                    //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Evaluate/Evaluate.h>



std::string NAMESPACE_EXPECT Evaluate::messagePrefix() {
  // Try to read the line
  std::string lineText = "";
  FILE *handle = std::fopen(file, "r");
  if (handle != NULL) {
    fseek(handle, 0, SEEK_END);
    long length = ftell(handle);
    fseek(handle, 0, SEEK_SET);
    if (char *contents = (char *)malloc(length + 1)) {
      if (fread(contents, 1, length, handle) == length) {
        contents[length] = 0;
        int _line = 1;
        size_t index = 0;
        while (_line < line && index < length) {
          if (contents[index] == '\n')
            _line++;
          index++;
        }
        if (_line == line) {
          // Read the whole line
          size_t start = index;
          while (index < length && contents[index] != '\n')
            index++;
          
          // Trim leading whitespace
          while (start < index && std::isspace(contents[start]))
            start++;
          
          // Trim trailing whitespace
          while (start < index && std::isspace(contents[index - 1]))
            index--;
          contents[index] = 0;
          
          if (start < index) {
            lineText
              .append(": `")
              .append(contents + start)
              .append("`");
          }
        }
      }
      free(contents);
    }
    fclose(handle);
  }
  
  return std::string("Failure on line ")
    .append(std::to_string(line))
    .append(lineText)
    .append(", ");
}
