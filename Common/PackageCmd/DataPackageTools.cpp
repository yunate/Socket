#include "DataPackageTools.h"

std::string DataPackageTools::Package(const char* cBuffs, size_t nSize)
{
	std::string sRes("");
	sRes.append(1, BEGIN_FLAG);

	for (size_t i = 0; i < nSize; ++i)
	{
		char cTmp = cBuffs[i];

		if (BEGIN_FLAG == cTmp || END_FLAG == cTmp || ESCAPE_CHAR == cTmp || !cTmp)
		{
			sRes.append(1, ESCAPE_CHAR);
		}

		sRes.append(1, cTmp);
	}

	sRes.append(1, END_FLAG);
	return sRes;
}

std::list<std::string> DataPackageTools::UnPackage(char* cBuffs, size_t nSize, size_t& nOutSize)
{
	std::list<std::string> sResList;

	if (0 == nSize)
	{
		return sResList;
	}

	char cTmp = 0;
	int nIndex = 0;
	std::string sTmp("");

	while (nIndex < nSize)
	{
		cTmp = cBuffs[nIndex++];

		if (BEGIN_FLAG == cTmp)
		{
			while (nIndex < nSize)
			{
				cTmp = cBuffs[nIndex++];

				if (END_FLAG == cTmp)
				{
					sResList.push_back(sTmp);
					sTmp = "";
					break;
				}

				if (BEGIN_FLAG == cTmp)
				{
					break;
				}

				if (ESCAPE_CHAR == cTmp)
				{
					if (nIndex < nSize)
					{
						cTmp = cBuffs[nIndex++];
					}
				}

				sTmp.append(1, cTmp) ;
			}
		}
	}

	nOutSize = sTmp.size();
	if (nOutSize > 0)
	{
		memcpy(cBuffs, sTmp.data(), nOutSize);
	}

	return sResList;
}

std::list<std::string> DataPackageTools::UnPackage(std::string& sBuff)
{
	size_t nLength = sBuff.size();
	char* pBuff = new char(nLength);
	memcpy(pBuff, sBuff.data(), nLength);
	size_t nOut = 0;
	std::list<std::string> reses = UnPackage(pBuff, nLength, nOut);
	sBuff = "";
	sBuff.append(pBuff, nOut);
	delete pBuff;
	return reses;
}
