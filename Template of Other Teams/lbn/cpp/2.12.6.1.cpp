s+=str;//加个字符串
s+=ch;//加个字符
s.append(str);
s.append(str,1,3);//将str从1开始3个字符加在str后
s.append(str,2,string::npos);//将str从2开始到结尾加在str后
s.append(5,ch);
s.push_back(ch);
