#!/bin/bash

OLD="$1"
NEW="$2"

# sanity check in input args
if [ -z "$OLD" ] || [ -z "$NEW" ]; then
    cat <<EOF
Usage: $0 <old> <new>
Changes the ADT plugin revision number.
Example:
  cd tools/eclipse
  scripts/update_version.sh 0.1.2 0.2.3
EOF
    exit 1
fi

# sanity check on current dir
if [ `basename "$PWD"` != "eclipse" ]; then
    echo "Please run this from tools/eclipse."
    exit 1
fi

function do_replace() {
  IS_MAC=""
  if [[ $(uname) == "Darwin" ]]; then IS_MAC="1" ; fi

  for i in $*; do
    if [[ -f "$i" ]]; then
      echo "+ Updating: $i"
      if [[ $IS_MAC ]]; then
        sed -i "" -e "s/$SED_OLD/$SED_NEW/g" "$i"
      else
        sed -i -e "s/$SED_OLD/$SED_NEW/g" "$i"
      fi
    else
      echo "- Ignoring: $i"
    fi
  done
}

# Files that use the ".qualifier" suffix
SED_OLD="${OLD//./\.}\.qualifier"
SED_NEW="${NEW//./\.}\.qualifier"
do_replace $(grep -rl "$SED_OLD" * | grep -E "\.xml$|\.MF$|\.product$")

# Specific files that do not use the .qualifier suffix.
# We hand-pick them instead of using a generic regexp, to avoid bogus replacements.
SED_OLD="${OLD//./\.}"
SED_NEW="${NEW//./\.}"
do_replace \
  plugins/com.android.ide.eclipse.monitor/monitor.product \
  plugins/com.android.ide.eclipse.monitor/plugin.properties

echo
echo "Remaining instances of $OLD"
# do another grep for older version without the qualifier. We don't
# want to replace those automatically as it could be something else.
# Printing out occurence helps find ones to update manually.
grep -r "$OLD" *

