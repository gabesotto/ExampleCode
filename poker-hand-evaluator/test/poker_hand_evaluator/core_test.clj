(ns poker-hand-evaluator.core-test
  (:require [clojure.test :refer :all]
            [poker-hand-evaluator.core :refer :all]))

(def high-seven                   ["2H" "3S" "4C" "5C" "7D"])
(def pair-hand                    ["2H" "2S" "4C" "5C" "7D"])
(def two-pairs-hand               ["2H" "2S" "4C" "4D" "7D"])
(def three-of-a-kind-hand         ["2H" "2S" "2C" "4D" "7D"])
(def four-of-a-kind-hand          ["2H" "2S" "2C" "2D" "7D"])
(def straight-hand                ["2H" "3S" "6C" "5D" "4D"])
(def low-ace-straight-hand        ["2H" "3S" "4C" "5D" "AD"])
(def high-ace-straight-hand       ["TH" "AS" "QC" "KD" "JD"])
(def flush-hand                   ["2H" "4H" "5H" "9H" "7H"])
(def full-house-hand              ["2H" "5D" "2D" "2C" "5S"])
(def straight-flush-hand          ["2H" "3H" "6H" "5H" "4H"])
(def low-ace-straight-flush-hand  ["2D" "3D" "4D" "5D" "AD"])
(def high-ace-straight-flush-hand ["TS" "AS" "QS" "KS" "JS"])
(def royal-flush-hand             ["AH" "TH" "JH" "QH" "KH"])

(deftest suit-test
  (testing "Suit"
    (is (= (suit "QH") "H"))))

(deftest rank-test
  (testing "Rank"
    (is (= (rank "TS") 10))))

(deftest high-card-test
  (testing "High Card"
    (is (= (high-card? high-seven) true))))

(deftest pair-test
  (testing "Pair"
    (is (= (pair? pair-hand) true))))

(deftest two-pair-test
  (testing "Two pair"
    (is (= (two-pairs? two-pairs-hand) true))))

(deftest three-of-a-kind-test
  (testing "Three of a kind"
    (is (= (three-of-a-kind? three-of-a-kind-hand) true))))

(deftest four-of-a-kind-test
  (testing "Four of a kind"
    (is (= (four-of-a-kind? four-of-a-kind-hand) true))))

(deftest flush-test
  (testing "Flush"
    (is (= (flush? flush-hand) true))))

(deftest full-house-test
  (testing "Full House"
    (is (= (full-house? full-house-hand) true))))

(deftest straight-low-test
  (testing "Straight"
    (is (= (straight? low-ace-straight-hand) true))))

(deftest straight-high-test
  (testing "Straight"
    (is (= (straight? high-ace-straight-hand) true))))

(deftest straight-flush-test
  (testing "Straight flush"
    (is (= (straight-flush? straight-flush-hand) true))))

(deftest royal-flush-test
  (testing "Royal Flush"
    (is (= (royal-flush? royal-flush-hand) true))))
