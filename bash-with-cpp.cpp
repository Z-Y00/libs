std::string execString;
execString="foo.sh";
const char* tmp=execString.c_str();
system(tmp);
