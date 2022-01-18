// Copyright Playspace S.L. 2017

using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    public class JsonUE4 : ModuleRules
    {
        public JsonUE4(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
            PrivateIncludePaths.Add("JsonUE4/Private");
            
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "Json"
                });

            PrivateIncludePathModuleNames.AddRange(
                new string[] {
                }
            );
        }
    }
}
