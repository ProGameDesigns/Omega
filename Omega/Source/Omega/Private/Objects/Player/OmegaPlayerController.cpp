// Fill out your copyright notice in the Description page of Project Settings.

#include "Omega/Public/Objects/Player/OmegaPlayerController.h"

//#include "Http/HttpGetWebsiteData.h"


#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Engine/Engine.h"

void AOmegaPlayerController::BeginPlay()
{
	Super::BeginPlay();

// 	FString PayloadString("");
// 	HTTPDATA = new FHttpGetWebsiteData(FString("POST"), PayloadString, TEXT("localhost/software/testData"), 1);
// 
// 	HTTPDATA->Run();


	//Run();
}


void AOmegaPlayerController::Run(void)
{
	Verb = "GET";
	Url = "https://www.itsknowledgecenter.net/2020/09/Refurbished-meaning.html";

	UE_LOG(LogHttp,Log,TEXT("Starting test [%s] Url=[%s]"),
		*Verb,*Url);

	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this,&AOmegaPlayerController::RequestComplete);
	//This is the url on which to process the request
	Request->SetURL("localhost/software/testData");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"),"X-UnrealEngine-Agent");
	Request->ProcessRequest();
}

void AOmegaPlayerController::RequestComplete(FHttpRequestPtr HttpRequest,FHttpResponsePtr HttpResponse,bool bSucceeded)
{
	UE_LOG(LogHttp,Log,TEXT("REQUEST COMPLETE STARTING [%s] Url=[%s]"),
		*Verb,*Url);

	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader,JsonObject))
	{
		//Get the value of the json object by field name
		int32 recievedInt = JsonObject->GetIntegerField("1");

		//Output it to the engine
		GEngine->AddOnScreenDebugMessage(1,2.0f,FColor::Green,FString::FromInt(recievedInt));
	}

}