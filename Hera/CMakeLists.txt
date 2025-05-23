set(TargetName Hera)

juce_add_plugin("${TargetName}"
        # VERSION ...
        # ICON_BIG ...
        # ICON_SMALL ...
        COMPANY_NAME "Poss"
        IS_SYNTH TRUE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE Poss
        PLUGIN_CODE Hera
        FORMATS AU VST3 Standalone
        PRODUCT_NAME "${TargetName}"
)
juce_generate_juce_header(${TargetName})

target_sources(${TargetName} PRIVATE
        Source/Processor.cpp
        Source/Processor.hpp
        Source/Integrator.hpp

		Source/Synth/AudioSource.cpp
		Source/Synth/AudioSource.hpp
		Source/Synth/Voice.cpp
		Source/Synth/Voice.hpp

		Source/Gui/Editor.cpp
		Source/Gui/Editor.hpp
)

target_include_directories(${TargetName} PUBLIC
		./Source
)

target_compile_definitions(${TargetName}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(${TargetName} PRIVATE
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags
        juce_audio_utils
)
