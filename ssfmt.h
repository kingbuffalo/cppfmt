#ifndef __SS_FMT_H__
#define __SS_FMT_H__
#include <iostream>
#include <sstream>
#include <cstring>

namespace buffalo{
	namespace ssfmt{
		namespace _buffalo_private{
			enum class CHAR_TYPE  {
				STR = 0,
				PARAMBEGIN = 1,
				PARAM = 2,
				PARAMEND = 3,
				STRSPEC = 4,
			};

			void GetDigIndex(const char* szFmt,int len,int begin,int &b,int &e, int &index){
				static char char2Type[128] = {0};
				if (int idx='{';char2Type[idx] == 0 ) {
					char2Type[idx] = 1;
					idx = '}';
					char2Type[idx] = 3;
					idx = '\\';
					char2Type[idx] = 4;
					for ( int i='0';i<'9'; i++ ){
						char2Type[i] = 2;
					}
				}
				int argIdx = 0;
				bool bFound = false;
				CHAR_TYPE pct = CHAR_TYPE::STR;
				for ( int i=begin;i<len;i++ ){
					CHAR_TYPE ct = static_cast<CHAR_TYPE>(char2Type[static_cast<int>(szFmt[i])]);
					if ( ct == CHAR_TYPE::PARAMBEGIN && pct != CHAR_TYPE::STRSPEC){
						b = i;
					}else if ( pct == CHAR_TYPE::PARAM && ct == CHAR_TYPE::PARAMEND ){
						e = i;
						break;
					}else if ( ct == CHAR_TYPE::PARAM && (pct == CHAR_TYPE::PARAMBEGIN || pct == CHAR_TYPE::PARAM)){
						bFound = true;
						argIdx = argIdx*10 + szFmt[i]-'0';
					}
					pct = ct;
				}
				index = bFound ? argIdx : -1;
			}

			void _GenStr(std::stringstream &ss,int idx){
			}

			template<typename T, typename... Args>
				void _GenStr(std::stringstream &ss,int idx,T&& t,Args&&... args){
					if ( idx == 0 ){
						ss << t;
					}
					if ( sizeof...(args) > 0  ){
						_GenStr(ss,idx-1,std::forward<Args>(args)...);
					}
				}
		}

		template<typename... Args>
			void ssfmt(std::stringstream &ss,const char* szFmt,Args&&... args){
				int len = strlen(szFmt);
				int argLen = sizeof...(args);
				int idx = 0;
				int b=0;
				int e=0;
				int argIdx=0;
				while( idx<len ){
					_buffalo_private::GetDigIndex(szFmt,len,idx,b,e,argIdx);
					if ( argIdx >= 0 ){
						ss.write(szFmt+idx,b-idx);
						if ( argIdx <  argLen ){
							_buffalo_private::_GenStr(ss,argIdx,std::forward<Args>(args)...);
						}
						idx = e+1;
					}else{
						ss.write(szFmt+idx,len-idx);
						break;
					}
				}
			}

		template<typename... Args>
			std::string sfmt(const char* szFmt,Args&&... args){
				std::stringstream ss;
				ssfmt(ss,szFmt,std::forward<Args>(args)...);
				return ss.str();
			}

		template<typename... Args>
			void fmt(const char* szFmt,Args&&... args){
				auto str = sfmt(szFmt,std::forward<Args>(args)... );
				std::cout << str << std::endl;
			}
	}
}

#endif
