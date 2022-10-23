# Example Non AI Template

This repository is an example template of what a project could look like. It uses the tinygltf header to parse and load a input gltf file for both encoder and decoder.

You can use this repository as a reference or starting point for your project.

## Creating Your Repository

Create a new repository for your project within this GitHub organization. You can use the `Use this template` button on GitHub to create a copy of this repository for your team. Use your team name for the repository name and make sure all your team members have access to your repository. To add them go to `Settings` then `Collaborators and teams`.

Then set up your new repository locally. You can clone it or use GitHub Desktop. Both options are available on the `Code` dropdown menu. To clone your repository and checkout the submodules use the following Git commands.

```
git clone [YourRepositoryGitURL]
cd [YourRepositoryName]
git submodule update --init --recursive
```

Now you are ready to start building your solution.


## Building the Executables

Run the `scripts/build_non_ai.sh` script to build the executables.

```
bash scripts/build_non_ai.sh
```

This is just a template, you need to write your own code to compress and decompress the `.obj` or `.glTF` sample files.

The build script creates the following symlinks to the executables so that the test script can run them.

- `encoder` this points to the *build/bin/encoder* executable.
- `decoder` this points to the *build/bin/decoder* executable.

If you want to create your own build script you can copy `scripts/build_non_ai.sh` outside the scripts folder (you cannot modify the scripts folder). Make sure to also update the `.github/workflows/ci.yml` file to run your new script on GitHub Actions.

## Testing the Executables

The `scripts/test_non_ai.sh` script runs all the sample models through the encoder and decoder.

```
bash scripts/test_non_ai.sh
```

The test script measures the **compression ratio**, **decompression time** and **image quality** for each sample model and then calculates a **weighted average** score.

It writes the compressed and decompressed files to the `test` folder.

And it logs the values for each model to the log files.

- `test/compression.log` the format is *Encoded/Failed FilePath CompressionRatio*
- `test/decompression.log` the format is *Decoded/Failed FilePath DecompressionTime*
- `test/quality.log` the format is *Quality/Failed FilePath PSNR*

## Support

Check the [FAQs](https://github.com/UKTechArena/.github/blob/main/FAQ.md)

If you still have any questions or experience any problems please reach out to us on the [#support](https://app.slack.com/client/T0447CNHDT2/C046F57C0C8) channel on Slack.
