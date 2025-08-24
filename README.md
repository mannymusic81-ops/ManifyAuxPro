# MaNiFy Aux Pro — Full Prototype (VST3/AU/Standalone)

This JUCE plugin project implements **mode switching** (Pads, Bells, Ambient, Hits, Pluck) with an animated UI indicator.
Samples are **embedded** as BinaryData for reliable loading in DAWs.

## Build (Projucer → Xcode)

1. Open `MaNiFyAuxPro.jucer` in **Projucer**.
2. In **Global Paths**, set your JUCE modules path (folder that contains `/modules`).
3. In **Exporters**, add **Xcode (macOS)**.
4. Ensure **Plugin Formats** include: VST3, AU, and Standalone.
5. Ensure **Enable plugin copy step** is checked.
6. **Save Project and Open in IDE** → Build.
7. Load the plugin in your DAW:
   - VST3: `~/Library/Audio/Plug-Ins/VST3/`
   - AU:    `~/Library/Audio/Plug-Ins/Components/`

## Build (Command Line)

If you prefer CMake, Projucer can create a CMake exporter; or just use the Xcode exporter with `xcodebuild`.

## Replacing Samples

Replace/augment the embedded WAVs by adding your own files to `Resources/Samples/` and marking them as **resource** in Projucer (so they compile into `BinaryData`). Update filenames in `PluginProcessor.cpp` if names change.

## Notes
- Hits and Pluck are momentary states; they auto-return to Pads.
- The analyser uses simple heuristics for MVP; we can refine thresholds later.
- UI is a simple dark/gold theme with a mode display and test buttons.
