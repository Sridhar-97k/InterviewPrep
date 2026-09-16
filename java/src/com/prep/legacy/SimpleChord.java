package com.prep.legacy;

import java.util.*;

class Node {
    int id;
    Node successor;
    Node predecessor;
    int m;
    List<Node> fingerTable;

    public Node(int id, int m) {
        this.id = id;
        this.m = m;
        this.fingerTable = new ArrayList<>(Collections.nCopies(m, null));
        this.successor = this;
        this.predecessor = null;
    }

    public void join(Node existingNode) {
        if (existingNode != null) {
            initFingerTable(existingNode);
            updateOthers();
        } else {
            for (int i = 0; i < m; i++)
                fingerTable.set(i, this);
            predecessor = this;
            successor = this;
        }
    }

    private void initFingerTable(Node existingNode) {
        fingerTable.set(0, existingNode.findSuccessor((id + 1) % (1 << m)));
        successor = fingerTable.get(0);
        predecessor = successor.predecessor;
        successor.predecessor = this;
    }

    private void updateOthers() {
        for (int i = 0; i < m; i++) {
            int predId = (id - (1 << i) + (1 << m)) % (1 << m);
            Node p = findPredecessor(predId);
            p.updateFingerTable(this, i);
        }
    }

    public void updateFingerTable(Node s, int i) {
        Node fi = fingerTable.get(i);
        if (fi == null || inInterval(s.id, this.id, fi.id)) {
            fingerTable.set(i, s);
            Node p = this.predecessor;
            if (p != null && p != this)
                p.updateFingerTable(s, i);
        }
    }

    public Node findSuccessor(int key) {
        Node n0 = findPredecessor(key);
        return n0.successor;
    }

    public Node findPredecessor(int key) {
        Node n = this;
        while (!inInterval(key, n.id, n.successor.id))
            n = n.closestPrecedingFinger(key);
        return n;
    }

    private Node closestPrecedingFinger(int key) {
        for (int i = m - 1; i >= 0; i--) {
            Node finger = fingerTable.get(i);
            if (finger != null && inInterval(finger.id, id, key))
                return finger;
        }
        return this;
    }

    private boolean inInterval(int key, int start, int end) {
        return start < end ? key > start && key <= end : key > start || key <= end;
    }

    @Override
    public String toString() {
        return "Node(" + id + ")";
    }
}

public class SimpleChord {
    public static void main(String[] args) {
        int m = 4;
        Node n1 = new Node(1, m);
        n1.join(null);
        Node n8 = new Node(8, m);
        n8.join(n1);
        Node n14 = new Node(14, m);
        n14.join(n1);
    }
}
