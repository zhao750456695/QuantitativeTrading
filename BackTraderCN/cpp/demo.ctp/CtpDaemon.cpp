#include "CtpTD.h"
#include "CtpMD.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <thread>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

#include "ThostFtdcTraderApi.h"

using namespace rapidjson;

using namespace std;

void readFromJson(std::vector<CThostFtdcInstrumentField>& instruments, std::string& filePath)
{
	ifstream ifs(filePath);
	IStreamWrapper isw(ifs);

	Document docRead;
	docRead.ParseStream(isw);
	if (docRead.HasParseError()) {
		std::cout << "error" << std::endl;
	}
	if (docRead.IsArray())
	{
		rapidjson::Value::Array instrumentArr = docRead.GetArray();
		int lengthOfInstrument = instrumentArr.Size();
		for (int i = 0; i < lengthOfInstrument; i++)
		{
			CThostFtdcInstrumentField field;
			memset(&field, 0, sizeof(CThostFtdcInstrumentField));
			strncpy(field.InstrumentID, instrumentArr[i]["InstrumentID"].GetString(), sizeof(field.InstrumentID));
			strncpy(field.ExchangeID, instrumentArr[i]["ExchangeID"].GetString(), sizeof(field.InstrumentID));
			instruments.push_back(field);
		}
	}
};


void save2Json(std::vector<CThostFtdcInstrumentField>& instruments, std::string& filePath)
{
	rapidjson::StringBuffer s;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	writer.StartArray();
	std::vector<CThostFtdcInstrumentField>::iterator itr;
	for (itr = instruments.begin(); itr != instruments.end(); itr++)
	{
		writer.StartObject();
		///��Լ����
		writer.Key("InstrumentID");
		writer.String(itr->InstrumentID);
		///����������
		writer.Key("ExchangeID");
		writer.String(itr->ExchangeID);
		///��Լ�ڽ������Ĵ���
		writer.Key("ExchangeInstID");
		writer.String(itr->ExchangeInstID);
		///��Ʒ����
		writer.Key("ProductID");
		writer.String(itr->ProductID);
		///��Ʒ����
		writer.Key("ProductClass");
		writer.String(std::string(1, itr->ProductClass).c_str());
		///�������
		writer.Key("DeliveryYear");
		writer.Int(itr->DeliveryYear);
		///������
		writer.Key("DeliveryMonth");
		writer.Int(itr->DeliveryMonth);
		///�м۵�����µ���
		writer.Key("MaxMarketOrderVolume");
		writer.Int(itr->MaxMarketOrderVolume);
		///�м۵���С�µ���
		writer.Key("MinMarketOrderVolume");
		writer.Int(itr->MinMarketOrderVolume);
		///�޼۵�����µ���
		writer.Key("MaxLimitOrderVolume");
		writer.Int(itr->MaxLimitOrderVolume);
		///�޼۵���С�µ���
		writer.Key("MinLimitOrderVolume");
		writer.Int(itr->MinLimitOrderVolume);
		///��Լ��������
		writer.Key("VolumeMultiple");
		writer.Int(itr->VolumeMultiple);
		///��С�䶯��λ
		writer.Key("PriceTick");
		writer.Double(itr->PriceTick);
		///������
		writer.Key("CreateDate");
		writer.String(itr->CreateDate);
		///������
		writer.Key("OpenDate");
		writer.String(itr->OpenDate);
		///������
		writer.Key("ExpireDate");
		writer.String(itr->ExpireDate);
		///��ʼ������
		writer.Key("StartDelivDate");
		writer.String(itr->StartDelivDate);
		///����������
		writer.Key("EndDelivDate");
		writer.String(itr->EndDelivDate);
		///��Լ��������״̬
		writer.Key("InstLifePhase");
		writer.String(std::string(1, itr->InstLifePhase).c_str());
		///��ǰ�Ƿ���
		writer.Key("IsTrading");
		writer.Bool(itr->IsTrading);
		///�ֲ�����
		writer.Key("PositionType");
		writer.String(std::string(1, itr->PositionType).c_str());
		///�ֲ���������
		writer.Key("PositionDateType");
		writer.String(std::string(1, itr->PositionDateType).c_str());
		///��ͷ��֤����
		writer.Key("LongMarginRatio");
		writer.Double(itr->LongMarginRatio);
		///��ͷ��֤����
		writer.Key("ShortMarginRatio");
		writer.Double(itr->ShortMarginRatio);
		///�Ƿ�ʹ�ô��߱�֤���㷨
		writer.Key("MaxMarginSideAlgorithm");
		writer.Double(itr->MaxMarginSideAlgorithm);
		///������Ʒ����
		writer.Key("UnderlyingInstrID");
		writer.String(itr->UnderlyingInstrID);
		///ִ�м�
		writer.Key("ProductClass");
		writer.String(std::string(1, itr->ProductClass).c_str());
		///��Ȩ����
		writer.Key("OptionsType");
		writer.String(std::string(1, itr->OptionsType).c_str());
		///��Լ������Ʒ����
		writer.Key("UnderlyingMultiple");
		writer.Double(itr->UnderlyingMultiple);
		///�������
		writer.Key("CombinationType");
		writer.String(std::string(1, itr->CombinationType).c_str());

		writer.EndObject();
	}
	writer.EndArray();

	ofstream ofs("instrument.json");
	if (ofs.is_open())
	{
		ofs << s.GetString() << std::endl;
		ofs.close();
	}
};


int main(int argc, char* argv[]) {
	ifstream ifs("ctp_config.json");
	IStreamWrapper isw(ifs);

	Document docRead;
	docRead.ParseStream(isw);

	string username = docRead["username"].GetString();
	string password = docRead["password"].GetString();
	string brokerID = docRead["brokerID"].GetString();
	string tdurl = docRead["tdUrl"].GetString();
	string mdurl = docRead["mdUrl"].GetString();
	
	CThostFtdcTraderApi* tdapi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CThostFtdcReqUserLoginField* loginField = new CThostFtdcReqUserLoginField();

	strncpy(loginField->UserID, username.c_str(), sizeof(loginField->UserID));
	strncpy(loginField->Password, password.c_str(), sizeof(loginField->Password));
	strncpy(loginField->BrokerID, brokerID.c_str(), sizeof(loginField->BrokerID));

	std::string filePath = "instruments.json";
	
	CtpTD* td = new CtpTD(tdapi, loginField);
	tdapi->RegisterSpi(td);

	tdapi->SubscribePublicTopic(THOST_TERT_RESTART);
	tdapi->SubscribePrivateTopic(THOST_TERT_RESTART);

	tdapi->RegisterFront((char *)tdurl.c_str());


	tdapi->Init();
	std::this_thread::sleep_for(std::chrono::seconds(10));

	
	std::vector<CThostFtdcInstrumentField> instruments = td->getInstruments();
	if (instruments.size() > 0)
	{
		save2Json(instruments, filePath);
	}
	else {
		readFromJson(instruments, filePath);
	}
	
	//start md
//	std::vector<CThostFtdcInstrumentField> instruments;
	readFromJson(instruments, filePath);
	CThostFtdcMdApi* mdapi = CThostFtdcMdApi::CreateFtdcMdApi();
	CtpMD* md = new CtpMD(mdapi, loginField);

	mdapi->RegisterSpi(md);
	
	mdapi->RegisterFront((char*)mdurl.c_str());
	mdapi->Init();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	int nCount = instruments.size();
	char** insts = new char* [nCount];
	for (int i = 0; i < nCount; i++)
	{
		insts[i] = (char*)instruments.at(i).InstrumentID;
		std::cout << insts[i] << std::endl;
	}

	int ret = mdapi->SubscribeMarketData(insts, nCount);

	mdapi->Join();
	return 0;
}