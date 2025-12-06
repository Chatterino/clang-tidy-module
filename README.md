This repository builds a clang-tidy module with checks specialized for the [Chatterino](https://github.com/Chatterino/chatterino2) project.

## Checks

### chatterino-explicit-this

When enabled, this check will warn for any usage of member methods or variables that are not prefixed with `this->`.

This implements `--fix`, which adds `this->` when required.

This currently avoids the `shared_from_this` name.
