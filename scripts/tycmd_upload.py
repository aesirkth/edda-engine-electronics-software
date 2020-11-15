Import("env")

env.Replace(
    UPLOADER="tycmd",
    UPLOADCMD="$UPLOADER upload $UPLOADERFLAGS $SOURCE"
)