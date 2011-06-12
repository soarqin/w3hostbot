#ifndef _XMLCONFIG_H_
#define _XMLCONFIG_H_

namespace Text
{
	class XmlConfig
	{
	public:
		XmlConfig(const char * filename);
		~XmlConfig();
		const char * GetString(const char *, const char *, const char *);
		int GetInteger(const char *, const char *, int);
		double GetReal(const char *, const char *, double);
		void ReadArray(std::vector<std::vector<std::string> >& result, std::vector<std::string>& keys, const char *, const char *);
	protected:
		void * _data;
	};
}

#endif // _XMLCONFIG_H_
