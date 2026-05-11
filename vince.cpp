#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <tuple>
#include <queue>
#include <chrono>
#include <stack>
#include <iomanip> 
#include <ctime>
#include <thread>  
using namespace std;

class Chatbot {
private:
    struct UserInfo {
        string name;
        int age;
        string education;
        string favoriteSubject;
        map<string, queue<int>> scores;
        map<string, int> topicCount;
        queue<tuple<string, string, int, int, int, string, string>> quizHistory;
        stack<tuple<int, string, string>> leaderboardScores;
        vector<string> rewards; 
    };

    UserInfo user;
    map<string, map<string, vector<pair<string, string>>>> quizzes;
public:
    Chatbot() {
        initializeQuizzes();
    }

    void run() {
        chatbotSay("Welcome to V-Chat! Let's make learning fun!");
        chatbotSay("Let me get to know you!");
        cout << endl;

        addInfo();
        string command;
        while (true) {
            cout << endl;
            printLine();
            chatbotSay("Tell me what you’d like to do:");
            cout << "> ";
            getline(cin, command);
            transform(command.begin(), command.end(), command.begin(), ::tolower);

            if (contains(command, "take") && contains(command, "quiz")) {
                this_thread::sleep_for(chrono::milliseconds(600));
                takeQuiz();
            } else if (contains(command, "check") && contains(command, "info")) {
                this_thread::sleep_for(chrono::milliseconds(600));
                checkInfo();
            } else if (contains(command, "check") && contains(command, "history")) {
                this_thread::sleep_for(chrono::milliseconds(600));
                showQuizHistory();
            } else if (contains(command, "check") && contains(command, "performance")) {
                this_thread::sleep_for(chrono::milliseconds(600));
                showBestOverallPerformance();
            } else if (contains(command, "check") && contains(command, "leaderboard")) {
                this_thread::sleep_for(chrono::milliseconds(600));
                showLeaderboard();
            } else if (command == "guidelines") {
                this_thread::sleep_for(chrono::milliseconds(600));
                showGuidelines();
            } else if (command == "exit") {
                this_thread::sleep_for(chrono::milliseconds(600));
                farewell();
                break;
            } else {
                chatbotSay("Sorry, I didn’t understand that. Type 'Guidelines' to see available commands.");
            }
        }
    }

private:
    void printLine(char ch = '=', int len = 40) {
        cout << string(len, ch) << endl;
    }

    bool contains(const string& input, const string& keyword) {
        return input.find(keyword) != string::npos;
    }

    string toLower(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    void initializeQuizzes() {
        quizzes["Math"]["Easy"] = {
            {"What is 2 + 2?", "4"},
            {"What is 3 * 3?", "9"},
            {"What is 10 - 5?", "5"},
            {"What is 1 + 1?", "2"},
            {"What is 5 + 3?", "8"},
            {"What is 4 * 2?", "8"},
            {"What is 9 - 4?", "5"},
            {"What is 7 + 1?", "8"},
            {"What is 8 - 3?", "5"},
            {"What is 6 * 2?", "12"}
        };
        quizzes["Math"]["Medium"] = {
            {"What is 6 * 7?", "42"},
            {"What is 12 / 4?", "3"},
            {"What is 15 - 8?", "7"},
            {"What is 8 * 9?", "72"},
            {"What is 18 / 3?", "6"},
            {"What is 25 - 6?", "19"},
            {"What is 9 * 7?", "63"},
            {"What is 35 / 5?", "7"},
            {"What is 14 + 9?", "23"},
            {"What is 45 - 10?", "35"}
        };
        quizzes["Math"]["Hard"] = {
            {"What is 25 * 18?", "450"},
            {"What is the square root of 144?", "12"},
            {"What is 15^3?", "3375"},
            {"What is 45 * 19?", "855"},
            {"What is 100 / 4?", "25"},
            {"What is 72 / 6?", "12"},
            {"What is 125 + 200?", "325"},
            {"What is 30 * 15?", "450"},
            {"What is 48 / 6?", "8"},
            {"What is 17 * 21?", "357"}
        };

        quizzes["Science"]["Easy"] = {
            {"What is H2O?", "Water"},
            {"What is the speed of light?", "299792458 m/s"},
            {"What is the boiling point of water?", "100°C"},
            {"What is the chemical symbol for oxygen?", "O"},
            {"What is the chemical symbol for hydrogen?", "H"},
            {"What is the primary gas in the Earth's atmosphere?", "Nitrogen"},
            {"What planet is closest to the Sun?", "Mercury"},
            {"What planet is known as the Red Planet?", "Mars"},
            {"What is the largest planet in the Solar System?", "Jupiter"},
            {"What is the human body's largest organ?", "Skin"}
        };
        quizzes["Science"]["Medium"] = {
            {"What is the chemical symbol for gold?", "Au"},
            {"What is the powerhouse of the cell?", "Mitochondria"},
            {"What is the atomic number of oxygen?", "8"},
            {"What is the process by which plants make their food?", "Photosynthesis"},
            {"What element is represented by the symbol Na?", "Sodium"},
            {"What is the chemical formula for methane?", "CH4"},
            {"Who developed the theory of relativity?", "Albert Einstein"},
            {"What is the name of our galaxy?", "Milky Way"},
            {"What element has the atomic number 1?", "Hydrogen"},
            {"What is the chemical symbol for sodium?", "Na"}
        };
        quizzes["Science"]["Hard"] = {
            {"What is the atomic mass of uranium?", "238.0289"},
            {"What is the speed of light in vacuum?", "299792458 m/s"},
            {"What element has the highest melting point?", "Tungsten"},
            {"Who discovered the electron?", "J.J. Thomson"},
            {"What is the most abundant element in the Earth's crust?", "Oxygen"},
            {"What is the name of the first man-made satellite?", "Sputnik 1"},
            {"What is the boiling point of helium?", "4.22 K"},
            {"What is the theory of quantum mechanics?", "A theory that explains the behavior of matter and energy at atomic and subatomic levels."},
            {"What is the name of the process by which light is converted into chemical energy?", "Photosynthesis"},
            {"What particle has a positive charge?", "Proton"}
        };

        quizzes["History"]["Easy"] = {
            {"Who was the first president of the USA?", "George Washington"},
            {"Who discovered America?", "Christopher Columbus"},
            {"What year did World War II end?", "1945"},
            {"Who was the first woman to fly solo across the Atlantic?", "Amelia Earhart"},
            {"What year did the Titanic sink?", "1912"},
            {"Who was the 16th president of the USA?", "Abraham Lincoln"},
            {"Who invented the telephone?", "Alexander Graham Bell"},
            {"What was the main cause of World War I?", "Assassination of Archduke Franz Ferdinand"},
            {"What is the capital of the Roman Empire?", "Rome"},
            {"In which year did the Berlin Wall fall?", "1989"}
        };
        quizzes["History"]["Medium"] = {
            {"Who wrote the Declaration of Independence?", "Thomas Jefferson"},
            {"What year did the Titanic sink?", "1912"},
            {"Who was the first woman to fly solo across the Atlantic?", "Amelia Earhart"},
            {"What was the name of the first manned moon mission?", "Apollo 11"},
            {"What year did the Battle of Hastings take place?", "1066"},
            {"Who was the last emperor of Rome?", "Romulus Augustulus"},
            {"Who was the leader of the Soviet Union during the Cuban Missile Crisis?", "Nikita Khrushchev"},
            {"What event sparked World War I?", "The assassination of Archduke Franz Ferdinand"},
            {"Who was the British prime minister during WWII?", "Winston Churchill"},
            {"What was the Cold War?", "A period of political tension between the Soviet Union and the United States"}
        };
        quizzes["History"]["Hard"] = {
            {"Who was the first emperor of China?", "Qin Shi Huang"},
            {"In which year did the Battle of Hastings take place?", "1066"},
            {"What was the main cause of the Cold War?", "Ideological conflict"},
            {"What was the name of the treaty that ended World War I?", "Treaty of Versailles"},
            {"Who was the longest-reigning British monarch before Queen Elizabeth II?", "Queen Victoria"},
            {"What was the name of the ship that brought the Pilgrims to America in 1620?", "Mayflower"},
            {"Who wrote the Communist Manifesto?", "Karl Marx and Friedrich Engels"},
            {"What was the name of the first manned mission to land on the Moon?", "Apollo 11"},
            {"Who was the first female prime minister of the UK?", "Margaret Thatcher"},
            {"What year did the U.S. Civil War end?", "1865"}
        };
    }

    void listQuizzes() {
        cout << endl;
        cout << "Available topics:\n";
        for (const auto& q : quizzes) {
            cout << "- " << q.first << endl;
        }
    }

    void takeQuiz() {
        cout << endl;
        string topic, difficulty;
        chatbotSay("You're about to start a quiz! Choose wisely.");
        chatbotSay("Tip: Try 'Easy' difficulty to warm up.");

        listQuizzes();
        cout << endl;
        cout << "Choose a topic to answer: ";
        getline(cin, topic);
        if (quizzes.find(topic) == quizzes.end()) {
            cout << "Topic not found. Try again!" << endl;
            return;
        }
        cout << endl;
        cout << "Choose difficulty (Easy/Medium/Hard): ";
        getline(cin, difficulty);

        transform(difficulty.begin(), difficulty.end(), difficulty.begin(), ::tolower);
        if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard") {
            cout << "Invalid difficulty level. Please choose 'Easy', 'Medium', or 'Hard'." << endl;
            return;
        }

        string correctDifficulty = difficulty == "easy" ? "Easy" :
                                  difficulty == "medium" ? "Medium" : "Hard";

        runQuiz(topic, correctDifficulty);
    }

    void runQuiz(const string& topic, const string& difficulty) {
        int correctAnswers = 0;
        int incorrectAnswers = 0;
        auto start = chrono::steady_clock::now();

        for (const auto& q : quizzes[topic][difficulty]) {
            string answer;
            cout << endl;
            cout << q.first << " " << endl << "> ";
            getline(cin, answer);
            this_thread::sleep_for(chrono::milliseconds(600));
            if (toLower(answer) == toLower(q.second)) {
                cout << "Correct! Well done!" << endl;
                correctAnswers++;
            } else {
                cout << "Oops! Incorrect. The correct answer is: " << q.second << "." << endl;
                incorrectAnswers++;
            }
        }

        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();
        string timeTaken = to_string(duration) + "s";

        auto now = chrono::system_clock::now();
        auto time = chrono::system_clock::to_time_t(now);
        string date = ctime(&time);
        date = date.substr(0, date.length() - 1);

        int total = quizzes[topic][difficulty].size();
        user.scores[topic].push(correctAnswers);
        user.topicCount[topic]++;
        user.quizHistory.push({topic, difficulty, correctAnswers, total, incorrectAnswers, timeTaken, date});
        user.leaderboardScores.push({correctAnswers, difficulty, topic});
        checkAndAwardRewards(correctAnswers, total, topic);

        chatbotSay("Let me check your answers...");
        this_thread::sleep_for(chrono::seconds(2));

        cout << "You got " << correctAnswers << " out of " << total << "." << endl;
        cout << "Time taken: " << timeTaken << endl;

        if (correctAnswers == total)
            chatbotSay("Awesome! You got a perfect score!");
        else if (correctAnswers >= total * 0.8)
            chatbotSay("Great job! Keep it up!");
        else if (correctAnswers >= total * 0.5)
            chatbotSay("Good effort, but you can do better!");
        else
            chatbotSay("Don't worry, keep practicing and you'll improve!");

        chatbotSay("\nWhat would you like to do now?");
        chatbotSay("1) Retake this quiz");
        chatbotSay("2) Change difficulty");
        chatbotSay("3) Next topic");
        chatbotSay("4) Main menu");
        cout << "> ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            runQuiz(topic, difficulty);
        } else if (choice == "2") {
            cout << "Enter new difficulty (Easy/Medium/Hard): ";
            string newDiff;
            getline(cin, newDiff);
            transform(newDiff.begin(), newDiff.end(), newDiff.begin(), ::tolower);
            if (newDiff == "easy" || newDiff == "medium" || newDiff == "hard") {
                string corrected = (newDiff == "easy" ? "Easy" : (newDiff == "medium" ? "Medium" : "Hard"));
                runQuiz(topic, corrected);
            } else {
                cout << "Invalid difficulty. Returning to main menu.\n";
            }
        } else if (choice == "3") {
            takeQuiz(); 
        } else {
            chatbotSay("Alright! Back to the main menu.");
        }
    }

    void addInfo() {
        chatbotSay("Please enter your name:");
        cout << "> ";
        getline(cin, user.name);
        chatbotSay("Hi " + user.name + "! What is your age?");
        cout << "> ";
        cin >> user.age;
        cin.ignore();

        chatbotSay("Got it! Let’s begin.");
        cout << "Information added! Thanks for sharing!" << endl;
    }

    void checkInfo() {
        cout << "\n=== Your Quiz Profile Info ===\n";
        cout << "Username: " << user.name << "\n";
        cout << "Age: " << user.age << " years old\n";  // Displaying the age
        cout << "Quizzes Taken: " << user.quizHistory.size() << "\n";

        if (user.quizHistory.empty()) {
            cout << "You haven’t taken any quizzes yet. Let’s get started and test your knowledge!\n";
            return;
        }

        double highestScore = -1;
        string bestTopic, bestDifficulty, bestDate;
        queue<tuple<string, string, int, int, int, string, string>> temp = user.quizHistory;

        while (!temp.empty()) {
            auto [topic, difficulty, correct, total, incorrect, timeTaken, date] = temp.front();
            temp.pop();
            double score = (double)correct / total * 100;

            if (score > highestScore) {
                highestScore = score;
                bestTopic = topic;
                bestDifficulty = difficulty;
                bestDate = date;
            }
        }

        cout << "\n--- Your Best Quiz Performance ---\n";
        cout << "Topic: " << bestTopic << "\n";
        cout << "Difficulty: " << bestDifficulty << "\n";
        cout << "Score: " << fixed << setprecision(2) << highestScore << "%\n";
        cout << "Date Taken: " << bestDate << "\n";
        cout << "\n--- Rewards Earned ---\n";
        if (user.rewards.empty()) {
            cout << "No rewards yet. Keep learning and you'll earn some soon!\n";
        } else {
            for (const auto& r : user.rewards) {
                cout << "- " << r << "\n";
            }
        }
        cout << "\nChatbot Feedback:\n";
        if (highestScore >= 90) {
            cout << "Amazing job! You truly aced your quiz in " << bestTopic << ". Keep up the excellent work!\n";
        } else if (highestScore >= 75) {
            cout << "Nice! You're showing strong skills in " << bestTopic << ". You're well on your way to mastery.\n";
        } else if (highestScore >= 50) {
            cout << "You're doing okay, but there's room to grow. Review your mistakes and try again—you're getting there!\n";
        } else {
            cout << "Looks like that quiz was a tough one. Don’t give up—you’re building a foundation with every attempt!\n";
        }
    }

    void showQuizHistory() {
        if (user.quizHistory.empty()) {
            cout << "No quiz history found. Start a quiz to build your history!" << endl;
            return;
        }
        vector<tuple<string, string, int, int, int, string, string>> historyVec;
        queue<decltype(user.quizHistory)::value_type> temp = user.quizHistory;

        while (!temp.empty()) {
            historyVec.push_back(temp.front());
            temp.pop();
        }
        reverse(historyVec.begin(), historyVec.end());

        cout << "Your Quiz History (Latest First):\n";
        for (const auto& [topic, diff, correct, total, incorrect, timeTaken, date] : historyVec) {
            cout << "- " << topic << " (" << diff << "): "
                 << correct << "/" << total << " correct, "
                 << incorrect << " incorrect, "
                 << "Time: " << timeTaken << ", Date: " << date << endl;
        }
    }

    void showLeaderboard() {
        if (user.leaderboardScores.empty()) {
            cout << "No quiz scores found for leaderboard. Start taking quizzes to get ranked!" << endl;
            return;
        }
        vector<tuple<int, string, string>> sortedScores;
        while (!user.leaderboardScores.empty()) {
            sortedScores.push_back(user.leaderboardScores.top());
            user.leaderboardScores.pop();
        }
        sort(sortedScores.begin(), sortedScores.end(), [](const auto& a, const auto& b) {
            return get<0>(a) > get<0>(b);
        });

        cout << "\n=== Leaderboard ===\n";
        set<string> shownTopics; // To show attempt count once per topic
        for (int i = 0; i < sortedScores.size(); ++i) {
            auto [score, difficulty, topic] = sortedScores[i];
            cout << "Rank " << i + 1 << ": " << score << " points (" << difficulty << " difficulty) - Topic: " << topic;
            if (shownTopics.find(topic) == shownTopics.end()) {
                int attempts = user.topicCount[topic];
                cout << " [Attempts: " << attempts << "]";
                shownTopics.insert(topic);
            }
            cout << endl;
        }
    }

    void showBestOverallPerformance() {
        cout << endl;
        if (user.quizHistory.empty()) {
            cout << "No quiz data available. Take some quizzes to evaluate your performance!" << endl;
            return;
        }

        map<string, int> correctByTopic, incorrectByTopic, totalByTopic;
        map<string, int> correctByDifficulty, incorrectByDifficulty;

        int totalCorrect = 0, totalQuestions = 0;
        double highestScore = -1;
        string bestQuizTopic, bestQuizDifficulty, bestQuizDate;

        queue<tuple<string, string, int, int, int, string, string>> temp = user.quizHistory;
        while (!temp.empty()) {
            auto [topic, difficulty, correct, total, incorrect, timeTaken, date] = temp.front();
            temp.pop();

            correctByTopic[topic] += correct;
            incorrectByTopic[topic] += incorrect;
            totalByTopic[topic] += total;
            correctByDifficulty[difficulty] += correct;
            incorrectByDifficulty[difficulty] += incorrect;

            double score = (double)correct / total * 100;
            if (score > highestScore) {
                highestScore = score;
                bestQuizTopic = topic;
                bestQuizDifficulty = difficulty;
                bestQuizDate = date;
            }

            totalCorrect += correct;
            totalQuestions += total;
        }

        double averageScore = (double)totalCorrect / totalQuestions * 100;

        cout << "\n=== Overall Performance Summary ===\n";
        cout << "Total Questions: " << totalQuestions << "\n";
        cout << "Correct Answers: " << totalCorrect << "\n";
        cout << fixed << setprecision(2);
        cout << "Average Score: " << averageScore << "%\n";

        if (averageScore >= 90) cout << "Outstanding performance! You're mastering the topics.\n";
        else if (averageScore >= 75) cout << "Great job! You're doing very well.\n";
        else if (averageScore >= 50) cout << "Good effort. You have some areas to review.\n";
        else cout << "Don't worry—keep practicing and you'll improve soon.\n";

        string bestTopic, worstTopic;
        double bestAccuracy = -1, worstAccuracy = 101;

        for (auto& [topic, correct] : correctByTopic) {
            int total = totalByTopic[topic];
            double acc = (double)correct / total * 100;
            if (acc > bestAccuracy) {
                bestAccuracy = acc;
                bestTopic = topic;
            }
            if (acc < worstAccuracy) {
                worstAccuracy = acc;
                worstTopic = topic;
            }
        }
        string mostCorrectDiff, mostIncorrectDiff;
        int maxCorrect = -1, maxIncorrect = -1;

        for (auto& [diff, count] : correctByDifficulty) {
            if (count > maxCorrect) {
                maxCorrect = count;
                mostCorrectDiff = diff;
            }
        }

        for (auto& [diff, count] : incorrectByDifficulty) {
            if (count > maxIncorrect) {
                maxIncorrect = count;
                mostIncorrectDiff = diff;
            }
        }

        cout << "\n--- Strengths & Weaknesses ---\n";
        cout << "Your Strength: You perform best in **" << bestTopic << "** with " << bestAccuracy << "% accuracy.\n";
        cout << "Your Weakness: You struggle most in **" << worstTopic << "** with " << worstAccuracy << "% accuracy.\n";

        cout << "\n--- Topic & Difficulty Insights ---\n";
        cout << "Most Correct Topic: " << bestTopic << " (" << correctByTopic[bestTopic] << " correct)\n";
        cout << "Most Incorrect Topic: " << worstTopic << " (" << incorrectByTopic[worstTopic] << " incorrect)\n";
        cout << "Most Correct Difficulty: " << mostCorrectDiff << " (" << correctByDifficulty[mostCorrectDiff] << " correct)\n";
        cout << "Most Incorrect Difficulty: " << mostIncorrectDiff << " (" << incorrectByDifficulty[mostIncorrectDiff] << " incorrect)\n";

        cout << "\n--- Best Quiz Performance ---\n";
        cout << "You performed best in the **" << bestQuizTopic << "** quiz (Difficulty: " << bestQuizDifficulty << ") on " << bestQuizDate << " with a score of " << highestScore << "%.\n";

        cout << "\n--- Feedback & Insights ---\n";
        if (averageScore >= 80) {
            cout << "You're showing excellent understanding overall. Focus on refining weaker areas like " << worstTopic << ".\n";
        } else if (averageScore >= 60) {
            cout << "Solid foundation! Try revisiting " << worstTopic << " and the " << mostIncorrectDiff << " level questions to boost your score.\n";
        } else {
            cout << "You're learning steadily. Prioritize practice in " << worstTopic << " and work up from " << mostIncorrectDiff << " difficulty to build confidence.\n";
        }
    }

    void checkAndAwardRewards(int score, int total, const string& topic) {
        double percent = (double)score / total * 100;
        string reward;

        if (percent == 100) {
            reward = "Perfect Score Badge";
        } else if (percent >= 90) {
            reward = "Gold Quizzer Badge";
        } else if (user.topicCount[topic] == 5) {
            reward = "Topic Explorer Badge (" + topic + ")";
        }

        if (!reward.empty() && find(user.rewards.begin(), user.rewards.end(), reward) == user.rewards.end()) {
            user.rewards.push_back(reward);
            chatbotSay("Congratulations! You've earned: " + reward);
        }
    }

    void showGuidelines() {
        cout << endl;
        chatbotSay("Here's what I can help you with:");
        cout << "- Add Info: Enter your information\n";
        cout << "- Take Quiz: Take a quiz on a subject\n";
        cout << "- History: View your quiz history\n";
        cout << "- Leaderboard: View the leaderboard\n";
        cout << "- Topic Progress: View answered and unanswered topics\n";
        cout << "- Exit: Quit the chat\n";
    }

    void chatbotSay(const string& message, int delay = 30) {
        for (char c : message) {
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(delay));    	
        }
        cout << endl;
    }

    void farewell() {
        cout << endl;
        cout << "===================================================" << endl;
        cout << "Thanks for learning with V-Chat. See you next time!" << endl;
        cout << "===================================================" << endl;
    }
};

int main() {
    Chatbot bot;
    bot.run();
    return 0;
}