//NTRHostage

#include "UAVGScriptText.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"

UUAVGScriptText::UUAVGScriptText()
{

}

TArray<FString> UUAVGScriptText::GetLocalizedScriptLines()
{
	TArray<FString> LocalizedScriptTextLine;

	for (const FText& txt : ScriptLines)
	{
		FString str = txt.ToString();
		if (str.StartsWith("$"))
		{
			str = str.Right(str.Len() - 1);
			bool flagFoundRelatedString = false;
			for (UStringTable* StringTable : StringTableToSearch)
			{
				FStringTableConstRef table = StringTable->GetStringTable();
				FStringTableEntryConstPtr entry = table.Get().FindEntry(str);
				if (entry.IsValid() && entry->GetDisplayString().IsValid())
				{
					str = *entry->GetDisplayString().Get(); // we get the localized string in table
					flagFoundRelatedString = true;//set flag
					break;//Exit loop
				}
			}

			if (!flagFoundRelatedString)
			{
				UE_LOG(LogTemp, Verbose, TEXT("%s not found in given string talble(s), this may be a variable"), *str);
				// we will parse variables in components later
			}

			str.Append("[l]"); //For it's a speaker string, no matter it's a variable or a localized string
		}
		
		if (str.StartsWith("^")) //This is a comment, skip all comments
			continue;
		
		LocalizedScriptTextLine.Add(str);
	}

	return LocalizedScriptTextLine;
}

#ifdef WITH_EDITOR
void UUAVGScriptText::EditorSetupScriptText(const FString& ScriptString, const FString& FilePath)
{
	TArray<FString> StrScriptLines;
	ScriptString.ParseIntoArrayLines(StrScriptLines, true);//Culled out all empty lines here

	for (const FString& str : StrScriptLines)
	{
		ScriptLines.Add(FText::FromString(str));
	}

	SourceFilename = FilePath;
}

TArray<UStringTable*> UUAVGScriptText::GetStringTableToSearch() const
{
	return StringTableToSearch;
}

void UUAVGScriptText::OnReimported(const TArray<UStringTable*>& OldStringTableToSearch)
{
	StringTableToSearch = OldStringTableToSearch;
}
#endif
