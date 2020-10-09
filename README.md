- CS106B assignments using the 2013 materials (http://stanford.edu/class/archive/cs/cs106b/cs106b.1136/).
- The original StanfordLCCPLib files do not work - just architecture? Current resolution:
  - Recompiled StanfordLCCPLib from source (https://cs.stanford.edu/people/eroberts/StanfordCPPLib/), on the same machine used to complete the projects. XCode 12.01, Mac OS Catalina 10.15.6.
  - Copied to global `/lib` directory for the whole course
  - For assignments (with course-provided projects): Replaced project `StandfordCCPLib` directory and `spl.jar` file with symlinks to `/lib` directory.
  - For sections (with projects created from scratch): referneced 
Previously tried:
  - Updating each XCode project to point to the `/lib` directory - would compile successfully, but would fail at runtime to find the `spl.jar` file. Tried placing this file in a parent directory, and in the globala Java `Extensions` directory. 
  - Tried configuring XCode to copy the file to the build output directory, but didn't seem to actually copy it.
