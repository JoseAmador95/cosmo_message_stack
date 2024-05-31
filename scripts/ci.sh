SCRIPT_PATH=$(dirname $(realpath -s $0))
WORKFLOW_PATH="${SCRIPT_PATH}/../.github/workflows/ci.yml"
COMMANDS=$(yq -r '.jobs.tests.steps[] | select(has("run")).run' < ${WORKFLOW_PATH})
while IFS= read -r COMMAND; do
    echo "Running: ${COMMAND}"
    eval "${COMMAND}"
done <<< "$COMMANDS"