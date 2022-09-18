import argparse
import os

# Parser
import re

parser = argparse.ArgumentParser(description="Runs autotester")
parser.add_argument("--autotester_path", help="Autotester path", required=True)
parser.add_argument("--test_dir", help="Tests folder", required=True)
parser.add_argument("--os", help="Tests folder", choices=["mac", "windows"], required=True)
parser.add_argument("--debug", help="Debug flag", choices=["true", "false"], default=False)
args = parser.parse_args()

# Test arguments
autotester_path: str = args.autotester_path
test_dir_arg: str = args.test_dir
os_type: str = args.os
debug: str = args.debug

# Scripts
# Comment out tests that you don't want to test
test_array = (
    # Milestone 1 tests
    ("Entities Only", "entities_only"),
    ("Follows / FollowsT", "follows_follows_t"),
    ("Semantic Errors", "semantic_errors"),
    ("Syntax Errors", "syntax_errors"),
    ("Patterns Only", "patterns_only"),
    # ("Parent / ParentT", "parent_parent_t"),
    # ("Uses Procedure", "uses_p"),
    # ("Uses Statement", "uses_s"),
    # ("Modifies Procedure", "modifies_p"),
    # ("Modifies Statement", "modifies_s"),
    ("Clause and Pattern", "clause_and_pattern")
)

overall_passed_test_cases = 0
overall_failed_test_cases = 0
overall_exception_test_cases = 0

for test in test_array:
    test_name = test[0]
    test_dir = test[1]
    source_path = f"{test_dir_arg}/{test_dir}/test_{test_dir}_source.txt"
    queries_path = f"{test_dir_arg}/{test_dir}/test_{test_dir}_queries.txt"
    output_path = f"{test_dir_arg}/out.xml"
    print(f"--- Running {test_name} Test ---")
    command = f"{autotester_path} {source_path} {queries_path} {output_path}"
    if os_type == 'windows':
        command = command.replace("/", "\\")
        if not debug:
            command += "> nul"
        else:
            print(command)
        output_path = output_path.replace("/", "\\")
    else:
        if not debug:
            command += "> /dev/null"
        else:
            print(command)
    os.system(command)
    with open(output_path) as f:
        output = f.read()
        passed_test_cases = []
        exception_test_cases = []
        failed_test_cases = []
        for query in output.split("<query>")[1:]:
            query_id = None
            if match := re.search('.*>(.*)</id>.*', query, re.IGNORECASE):
                query_id = match.group(1)

            comment = None
            if match := re.search('.*comment="(.*)">.*', query, re.IGNORECASE):
                comment = match.group(1)

            stuans = None
            if match := re.search('.*<stuans>(.*)</stuans>.*', query, re.IGNORECASE):
                stuans = match.group(1)

            correct = None
            if match := re.search('.*<correct>(.*)</correct>.*', query, re.IGNORECASE):
                correct = match.group(1)

            if "<passed/>" in query:
                passed_test_cases.append([query_id, comment])

            if "<exception/>" in query:
                exception_test_cases.append([query_id, comment])

            if "<failed>" in query:
                failed_test_cases.append(
                    [query_id, f"{comment} | Expected: '{correct}' | Returned: '{stuans}'"])

        overall_passed_test_cases += len(passed_test_cases)
        overall_failed_test_cases += len(failed_test_cases) + len(exception_test_cases)
        overall_exception_test_cases += len(exception_test_cases)
        print(
            f"Passed: {len(passed_test_cases)}, Failed: {len(failed_test_cases) + len(exception_test_cases)}, "
            f"Exceptions (subset of failures): {len(exception_test_cases)}")
        if failed_test_cases:
            print("\nFailed cases:")
            for failed_id, failed_comment in failed_test_cases:
                print(f"{failed_id} - {failed_comment}")
        if exception_test_cases:
            print("\nException cases:")
            for exception_id, exception_comment in exception_test_cases:
                print(f"{exception_id} - {exception_comment}")
    print("")

print("=== Test Summary ===")
print(f"Total Passed: {overall_passed_test_cases}")
print(f"Total Failed: {overall_failed_test_cases}")
print(f"Total Exceptions (subset of failures): {overall_exception_test_cases}")

if overall_failed_test_cases > 0:
    exit(1)

exit(0)
