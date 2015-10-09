Design Cache with auto deletion
Design a cache for translation service. The cache has a limited size thus should be able to 
drop the oldest element when it’s full. Once an element in the cache is accessed, it should 
be treated as if it was just added to the cache.

We are using Hashtable to store the key-value data, we use linked list to keep track of the 
oldest element so it can be quickly removed from the Hashtable.

Test:

           Cache cache = new Cache(3);
           CacheKey cacheKey1 = new CacheKey("eng", "hebrew", "my home");
           cache.Insert(cacheKey1, "הבית שלי");
           Assert.AreEqual(1, cache.Operations.Count);
           Assert.AreEqual(CacheOperationType.Added, cache.Operations[0].OperationType);
           cache.CleanOperationsLog();

           CacheKey cacheKey2 = new CacheKey("eng", "hebrew", "door");
           cache.Insert(cacheKey2, "דלת");
           Assert.AreEqual(1, cache.Operations.Count);
           Assert.AreEqual(CacheOperationType.Added, cache.Operations[0].OperationType);
           cache.CleanOperationsLog();

           CacheKey cacheKey3 = new CacheKey("eng", "hebrew", "license");
           cache.Insert(cacheKey3, "רשיון");
           Assert.AreEqual(1, cache.Operations.Count);
           Assert.AreEqual(CacheOperationType.Added, cache.Operations[0].OperationType);
           cache.CleanOperationsLog();

           CacheKey cacheKey4 = new CacheKey("eng", "hebrew", "king");
           cache.Insert(cacheKey4, "מלך");
           Assert.AreEqual(2, cache.Operations.Count);
           Assert.AreEqual(CacheOperationType.Removed, cache.Operations[0].OperationType);
           CacheKey operationKey = cache.Operations[0].CacheKey;
           Assert.AreEqual(cacheKey1, operationKey, "Removed key is not the first that was added");
           Assert.AreEqual(CacheOperationType.Added, cache.Operations[1].OperationType);
           cache.CleanOperationsLog();

           string translation = cache.Lookup(cacheKey2);
           Assert.AreEqual("דלת", translation);
           Assert.AreEqual(1, cache.Operations.Count);
           Assert.AreEqual(CacheOperationType.Refreshed, cache.Operations[0].OperationType);
           cache.CleanOperationsLog();

           CacheKey cacheKey5 = new CacheKey("eng", "hebrew", "moon");
           cache.Insert(cacheKey5, "ירח");
           Assert.AreEqual(2, cache.Operations.Count);
           Assert.AreEqual(CacheOperationType.Removed, cache.Operations[0].OperationType);
           operationKey = cache.Operations[0].CacheKey;
           Assert.AreEqual(cacheKey3, operationKey, "Removed key is not the first that was added");
       }

Solution:

    public class Cache
    {
        readonly LinkedList<CacheKey> linkedList = new LinkedList<CacheKey>();
        readonly Hashtable dic = new Hashtable();
        readonly List<CacheOperation> operations = new List<CacheOperation>();

        private readonly int maxItems;

        public Cache(int maxItems)
        {
            this.maxItems = maxItems;
        }

        public void Insert(CacheKey key, string translation)
        {
            if (linkedList.Count >= maxItems)
            {
                LinkedListNode<CacheKey> linkedItemToRemove = linkedList.First;
                CacheKey cacheKeyToRemove = linkedItemToRemove.Value;
                dic.Remove(cacheKeyToRemove);
                linkedList.Remove(linkedItemToRemove);
                operations.Add(new CacheOperation(CacheOperationType.Removed, cacheKeyToRemove));
            }

            LinkedListNode<CacheKey> linkedItemAdded = linkedList.AddLast(key);
            operations.Add(new CacheOperation(CacheOperationType.Added, key));
            dic.Add(key, new CacheValue(translation, linkedItemAdded));
        }

        public string Lookup(CacheKey key)
        {
            bool exist = dic.ContainsKey(key);
            if (exist)
            {
                var cacheValue = (CacheValue)dic[key];
                // Refresh item
                linkedList.Remove(cacheValue.LinkedListNode);
                linkedList.AddLast(key);
                operations.Add(new CacheOperation(CacheOperationType.Refreshed, key));
               
                return  cacheValue.Translation;
            }
            return null;
        }

        public List<CacheOperation> Operations
        {
            get { return operations; }
        }

        public void CleanOperationsLog()
        {
            operations.Clear();
        }
    }

    class CacheValue
    {
        private readonly string translation;
        private readonly LinkedListNode<CacheKey> linkedListNode;

        public CacheValue(string translation, LinkedListNode<CacheKey> linkedListNode)
        {
            this.translation = translation;
            this.linkedListNode = linkedListNode;
        }

        public string Translation
        {
            get { return translation; }
        }

        public LinkedListNode<CacheKey> LinkedListNode
        {
            get { return linkedListNode; }
        }
    }

    public class CacheKey
    {
        private readonly string fromLanguage;
        private readonly string toLanguage;
        private readonly string statement;

        public CacheKey(string fromLanguage, string toLanguage, string statement)
        {
            this.fromLanguage = fromLanguage;
            this.toLanguage = toLanguage;
            this.statement = statement;
        }

        public string FromLanguage
        {
            get { return fromLanguage; }
        }

        public string ToLanguage
        {
            get { return toLanguage; }
        }

        public string Statement
        {
            get { return statement; }
        }

        protected bool Equals(CacheKey other)
        {
            return string.Equals(fromLanguage, other.fromLanguage) && 
                string.Equals(toLanguage, other.toLanguage) && 
                string.Equals(statement, other.statement);
        }

        public override bool Equals(object obj)
        {
            return Equals((CacheKey) obj);
        }

        public override int GetHashCode()
        {
            return toLanguage.GetHashCode() ^ fromLanguage.GetHashCode() ^ statement.GetHashCode();
        }
    }

    public class CacheOperation
    {
        private readonly CacheOperationType operationType;
        private readonly CacheKey cacheKey;

        public CacheOperation(CacheOperationType operationType, CacheKey cacheKey)
        {
            this.operationType = operationType;
            this.cacheKey = cacheKey;
        }

        public CacheOperationType OperationType
        {
            get { return operationType; }
        }

        public CacheKey CacheKey
        {
            get { return cacheKey; }
        }
    }

    public enum CacheOperationType
    {
        Added,
        Removed,
        Refreshed
    }
