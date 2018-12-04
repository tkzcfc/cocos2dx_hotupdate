#include "json_lua.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "json/prettywriter.h"
#include "json/document.h"

std::string prettyJson(const std::string& content)
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	rapidjson::Document _json;
	// Parse file with rapid json
	_json.Parse<0>(content.c_str());
	// Print error
	if (_json.HasParseError()) {
		size_t offset = _json.GetErrorOffset();
		if (offset > 0)
			offset--;
		std::string errorSnippet = content.substr(offset, 10);
		printf("File parse error %d at <%s>\n", _json.GetParseError(), errorSnippet.c_str());
	}
	_json.Accept(writer);

	return buffer.GetString();
}


