#include "config.h"
#include "XmlConfig.h"
#include "common/File.h"
#include "mxml/mxml.h"

namespace Text
{
	XmlConfig::XmlConfig( const char * filename )
	{
		_data = NULL;
		Common::FileStream fs;
		if(!fs.Open(filename))
			return;
		uint size = (uint)fs.Size();
		if(size == 0)
			return;
		std::string buf;
		buf.resize(size);
		fs.Read(&buf[0], size);
		fs.Close();
		mxml_node_t * root = mxmlLoadString(NULL, &buf[0], NULL);
		_data = root;
	}

	XmlConfig::~XmlConfig()
	{
		if(_data != NULL)
		{
			mxmlDelete((mxml_node_t*)_data);
			_data = NULL;
		}
	}

	const char * XmlConfig::GetString( const char * sec, const char * name, const char * def )
	{
		if(_data == NULL)
			return def;
		mxml_node_t * root = (mxml_node_t *)_data;
		mxml_node_t * node = mxmlFindElement(root, root, sec, NULL, NULL, MXML_DESCEND_FIRST);
		if(node == NULL)
			return def;
		const char * result = mxmlElementGetAttr(node, name);
		if(result == NULL)
			return def;
		return result;
	}

	int XmlConfig::GetInteger( const char * sec, const char * name, int def )
	{
		const char * result = GetString(sec, name, NULL);
		if(result == NULL)
			return def;
		return atoi(result);
	}

	double XmlConfig::GetReal( const char * sec, const char * name, double def )
	{
		const char * result = GetString(sec, name, NULL);
		if(result == NULL)
			return def;
		return atof(result);
	}

	void XmlConfig::ReadArray( std::vector<std::vector<std::string> >& result, std::vector<std::string>& keys, const char * sec, const char * name )
	{
		result.clear();
		if(_data == NULL || keys.size() == 0)
			return;
		mxml_node_t * root = (mxml_node_t *)_data;
		mxml_node_t * node = mxmlFindElement(root, root, sec, NULL, NULL, MXML_DESCEND_FIRST);
		if(node == NULL)
			return;
		mxml_node_t * child = mxmlFindElement(node, node, name, NULL, NULL, MXML_DESCEND_FIRST);
		size_t c = keys.size();
		while(child != NULL)
		{
			std::vector<std::string> item;
			item.resize(c);
			for(size_t i = 0; i < c; ++ i)
			{
				const char * str = mxmlElementGetAttr(child, keys[i].c_str());
				if(str == NULL)
					continue;
				item[i] = str;
			}
			result.push_back(item);
			child = mxmlFindElement(child, node, name, NULL, NULL, MXML_NO_DESCEND);
		}
	}
}
