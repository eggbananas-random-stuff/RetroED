#include "libRSDK.hpp"

#include "stageconfigv4.hpp"

void RSDKv4::StageConfig::read(Reader &reader)
{
    filePath = reader.filePath;

    // Global Objects Flag
    loadGlobalScripts = reader.read<byte>();

    // Stage Palette
    palette.read(reader, 2 * 16);

    // Stage SoundFX
    byte sfxCount = reader.read<byte>();
    soundFX.clear();

    for (int s = 0; s < sfxCount; ++s) {
        SoundInfo obj;
        obj.name = reader.readString();
        soundFX.append(obj);
    }

    for (SoundInfo &sfx : soundFX) {
        sfx.path = reader.readString();
    }

    // Stage Objects
    int objectCount = reader.read<byte>();
    objects.clear();

    for (int o = 0; o < objectCount; ++o) {
        ObjectInfo obj;
        obj.name = reader.readString();
        objects.append(obj);
    }

    for (ObjectInfo &obj : objects) {
        obj.script = reader.readString();
    }
}

void RSDKv4::StageConfig::write(Writer &writer)
{
    filePath = writer.filePath;

    // Global Objects Flag
    writer.write(loadGlobalScripts);

    // Stage Palette
    palette.write(writer);

    // Stage SoundFX
    writer.write((byte)soundFX.count());
    for (SoundInfo &sfx : soundFX) {
        writer.write(sfx.name);
    }

    for (SoundInfo &sfx : soundFX) {
        writer.write(sfx.path);
    }

    // Stage Objects
    writer.write((byte)objects.count());
    for (ObjectInfo &obj : objects) {
        writer.write(obj.name);
    }

    for (ObjectInfo &obj : objects) {
        writer.write(obj.script);
    }

    writer.flush();
}
